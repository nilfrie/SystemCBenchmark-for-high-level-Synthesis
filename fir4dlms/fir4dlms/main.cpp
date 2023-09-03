//
// Main File to test fir4dlms module.
//

#include "fir4dlms.h"
#include "tb_fir4dlms.h"

int sc_main(int argc, char** argv) {
	sc_clock		clk("clk", 25, SC_NS, 0.5, 12.5, SC_NS, true);
	sc_signal<bool> rst;

	sc_signal<sc_int<W1>> x_in;
	sc_signal<sc_int<W1>> d_in;
	sc_signal<sc_int<W2>> y_out;
	sc_signal<sc_int<W1>> f0_out;
	sc_signal<sc_int<W1>> f1_out;
	sc_signal<sc_int<W2>> e_out;

	fir4dlms u_fir4dlms("FIR4DLMS");
	test_fir4dlms test_FIR4DLMS("TEST_FIR4DLMS");

	// Connect to module
	u_fir4dlms.clk(clk);
	u_fir4dlms.rst(rst);
	u_fir4dlms.x_in(x_in);
	u_fir4dlms.y_out(y_out);
	u_fir4dlms.d_in(d_in);
	u_fir4dlms.f0_out(f0_out);
	u_fir4dlms.f1_out(f1_out);
	u_fir4dlms.e_out(e_out);

	// Connect to testbench
	test_FIR4DLMS.clk(clk);
	test_FIR4DLMS.rst(rst);
	test_FIR4DLMS.x(x_in);
	test_FIR4DLMS.y(y_out);
	test_FIR4DLMS.d(d_in);
	test_FIR4DLMS.f0(f0_out);
	test_FIR4DLMS.f1(f0_out);
	test_FIR4DLMS.e(e_out);


	// Start Simulation
	sc_start(25, SC_NS);
	rst.write(1);

	sc_start(25, SC_NS);
	rst.write(0);

	sc_start();

	return 0;
}