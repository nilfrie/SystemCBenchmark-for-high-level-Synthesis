/*
* Main File to test magnitude module.
*/

#include "magnitude.h"
#include "tb_magnitude.h"

int sc_main(int argc, char** argv) {
	sc_clock		clk("clk", 25, SC_NS, 0.5, 12.5, SC_NS, true);
	sc_signal<bool> rst;

	sc_signal<sc_int<16>> x_in;
	sc_signal<sc_int<16>> y_in;
	sc_signal<sc_int<16>> r_out;

	magnitude u_magnitude("MAGNITUDE");
	test_magnitude test_Magnitude("TEST_MAGNITUDE");

	u_magnitude.clk(clk);
	u_magnitude.rst(rst);
	u_magnitude.x_in(x_in);
	u_magnitude.y_in(y_in);
	u_magnitude.r_out(r_out);

	test_Magnitude.clk(clk);
	test_Magnitude.rst(rst);
	test_Magnitude.x(x_in);
	test_Magnitude.y(y_in);
	test_Magnitude.r(r_out);

	// Start Simulation
	sc_start(25, SC_NS);
	rst.write(1);

	sc_start(25, SC_NS);
	rst.write(0);

	sc_start();

	return 0;
}