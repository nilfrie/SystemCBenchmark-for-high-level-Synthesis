/*
* Main File to test cordic module.
*/

#include "cordic.h"
#include "tb_cordic.h"

int sc_main(int argc, char** argv) {
	sc_clock	clk("clk", 25, SC_NS, 0.5, 12.5, SC_NS, true);
	sc_signal<bool> rst;
	sc_signal<sc_int<W>> x;				// System real or x input
	sc_signal<sc_int<W>> y;				// System imaginery or y input

	sc_signal<sc_int<W>> r;				// Radius result
	sc_signal<sc_int<W>> phi;			// Phase result
	sc_signal<sc_int<W>> eps;			// Error of results

	Cordic u_cordic("CORDIC");
	test_cordic test_Cordic("TEST_CORDIC");

	u_cordic.clk(clk);
	u_cordic.rst(rst);
	u_cordic.x_in(x);
	u_cordic.y_in(y);
	u_cordic.r_out(r);
	u_cordic.phi_out(phi);
	u_cordic.eps_out(eps);

	test_Cordic.tb_clk(clk);
	test_Cordic.tb_rst(rst);
	test_Cordic.tb_r_out(r);
	test_Cordic.tb_x_in(x);
	test_Cordic.tb_y_in(y);
	test_Cordic.tb_phi_out(phi);
	test_Cordic.tb_eps_out(eps);

	// Start Simulation
	sc_start(25, SC_NS);
	rst.write(1);

	sc_start(25, SC_NS);
	rst.write(0);

	sc_start();

	return 0;
}