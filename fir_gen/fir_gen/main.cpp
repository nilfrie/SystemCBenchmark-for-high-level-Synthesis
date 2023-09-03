//
// Main File to test fir_gen module.
//

#include "fir_gen.h"
#include "tb_fir_gen.h"

int sc_main(int argc, char** argv)
{
	sc_clock		clk("clk", 25, SC_NS, 0.5, 12.5, SC_NS, true);
	sc_signal<bool> rst;

	sc_signal<sc_int<W1>> x_in;
	sc_signal<sc_int<W1>> c_in;
	sc_signal<sc_int<W4>> y_out;
	sc_signal<bool> load_x;

	fir_gen u_fir_gen("FIR_GEN");
	test_fir_gen test_FIR_GEN("TEST_FIR_GEN");

	// Connect to module
	u_fir_gen.clk(clk);
	u_fir_gen.rst(rst);
	u_fir_gen.x_in(x_in);
	u_fir_gen.y_out(y_out);
	u_fir_gen.c_in(c_in);
	u_fir_gen.load_x(load_x);

	// Connect to testbench
	test_FIR_GEN.clk(clk);
	test_FIR_GEN.rst(rst);
	test_FIR_GEN.x(x_in);
	test_FIR_GEN.y(y_out);
	test_FIR_GEN.load_x(load_x);
	test_FIR_GEN.c(c_in);


	// Start Simulation
	sc_start(25, SC_NS);
	rst.write(1);

	sc_start(25, SC_NS);
	rst.write(0);

	sc_start();

	return 0;
}
