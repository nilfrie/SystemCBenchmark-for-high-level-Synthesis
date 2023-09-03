//
// Main File to test sqrt module.
//

#include "SQRT.h"
#include "tb_sqrt.h"

int sc_main(int argc, char** argv) {
	sc_clock		clk("clk", 25, SC_NS, 0.5, 12.5, SC_NS, true);
	sc_signal<bool> rst;

	sc_signal<sc_uint<32>> x_in;

	sc_signal<bool> load;

	sc_signal<sc_uint<32>> c_out;			// System output

	sc_signal<bool> c_ready;

	SQRT u_sqrt("SQRT");
	test_sqrt test_SQRT("TEST_SQRT");

	// Connect to module
	u_sqrt.clk(clk);
	u_sqrt.rst(rst);
	u_sqrt.x_in(x_in);
	u_sqrt.c_out(c_out);
	u_sqrt.c_ready(c_ready);
	u_sqrt.load(load);

	// Connect to testbench
	test_SQRT.clk(clk);
	test_SQRT.rst(rst);
	test_SQRT.x(x_in);
	test_SQRT.c(c_out);
	test_SQRT.c_ready(c_ready);
	test_SQRT.tb_load(load);


	// Start Simulation
	sc_start(25, SC_NS);
	rst.write(1);

	sc_start(25, SC_NS);
	rst.write(0);

	sc_start();

	return 0;
}