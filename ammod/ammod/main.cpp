/*
* Main File to test ammod module.
*/

#include "ammod.h"
#include "tb_ammod.h"

int sc_main(int argc, char** argv) {
	sc_clock	clk("clk", 25, SC_NS, 0.5, 12.5, SC_NS, true);
	sc_signal<bool> rst;
	sc_signal<sc_int<W + 1>> r;				// System real or x input
	sc_signal<sc_int<W + 1>> phi;				// System imaginery or y input

	sc_signal<sc_int<W + 1>> x;				// Radius result
	sc_signal<sc_int<W + 1>> y;			// Phase result
	sc_signal<sc_int<W + 1>> eps;			// Error of results

	ammod u_ammod("AMMOD");
	test_ammod test_Ammod("TEST_AMMOD");

	u_ammod.clk(clk);
	u_ammod.rst(rst);
	u_ammod.r_in(r);
	u_ammod.phi_in(phi);
	u_ammod.x_out(x);
	u_ammod.y_out(y);
	u_ammod.eps_out(eps);

	test_Ammod.tb_clk(clk);
	test_Ammod.tb_rst(rst);
	test_Ammod.tb_r_in(r);
	test_Ammod.tb_phi_in(phi);
	test_Ammod.tb_y_out(y);
	test_Ammod.tb_x_out(x);
	test_Ammod.tb_eps_out(eps);

	// Start Simulation
	sc_start(25, SC_NS);
	rst.write(1);

	sc_start(25, SC_NS);
	rst.write(0);

	sc_start();

	return 0;
}