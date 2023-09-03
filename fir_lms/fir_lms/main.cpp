//
// Main File to test fir_lms module.
//

#include "fir_lms.h"
#include "tb_fir_lms.h"


int sc_main(int argc, char** argv)
{
	sc_clock		clk("clk", 25, SC_NS, 0.5, 12.5, SC_NS, true);
	sc_signal<bool> rst;

	sc_signal<sc_int<W1>> x_in;
	sc_signal<sc_int<W1>> d_in;
	sc_signal<sc_int<W2>> y_out;
	sc_signal<sc_int<W1>> f0_out;
	sc_signal<sc_int<W1>> f1_out;
	sc_signal<sc_int<W2>> e_out;

	fir_lms u_fir_lms("FIR_LMS");
	test_fir_lms test_FIR_LMS("TEST_FIR_LMS");

	// Connect to module
	u_fir_lms.clk(clk);
	u_fir_lms.rst(rst);
	u_fir_lms.x_in(x_in);
	u_fir_lms.y_out(y_out);
	u_fir_lms.d_in(d_in);
	u_fir_lms.f0_out(f0_out);
	u_fir_lms.f1_out(f1_out);
	u_fir_lms.e_out(e_out);

	// Connect to testbench
	test_FIR_LMS.clk(clk);
	test_FIR_LMS.rst(rst);
	test_FIR_LMS.x(x_in);
	test_FIR_LMS.y(y_out);
	test_FIR_LMS.d(d_in);
	test_FIR_LMS.f0(f0_out);
	test_FIR_LMS.f1(f0_out);
	test_FIR_LMS.e(e_out);


	// Start Simulation
	sc_start(25, SC_NS);
	rst.write(1);

	sc_start(25, SC_NS);
	rst.write(0);

	sc_start();

	return 0;
}