/*
* Main File to test arctan module.
*/

#include "arctan.h"
#include "tb_arctan.h"

int sc_main(int argc, char** argv) {
	sc_clock	clk("clk", 25, SC_NS, 0.5, 12.5, SC_NS, true);
	sc_signal<bool> rst;

	sc_signal<sc_int<W>> x;

	sc_signal<sc_int<W>> f;

	arctan u_arctan("ARCTAN");
	test_arctan t_arctan("TEST_ARCTAN");

	u_arctan.clk(clk);
	u_arctan.rst(rst);
	u_arctan.x_in(x);
	u_arctan.f_out(f);

	t_arctan.tb_clk(clk);
	t_arctan.tb_rst(rst);
	t_arctan.tb_x_in(x);
	t_arctan.tb_f_out(f);

	// Start Simulation

	sc_start(25, SC_NS);
	rst.write(0);

	sc_start();

	return 0;
}