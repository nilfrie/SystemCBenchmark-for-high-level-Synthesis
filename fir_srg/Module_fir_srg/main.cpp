//
// Main File to test fir_srg module.
//

#include "fir_srg.h"
#include "tb_fir_srg.h"

int sc_main(int argc, char** argv)
{
	sc_clock		clk("clk", 25, SC_NS, 0.5, 12.5, SC_NS, true);
	sc_signal<bool> rst;

	sc_signal<sc_int<8>> x_in;
	sc_signal<sc_int<8>> y_in;

	fir_srg u_FIR_SRG("FIR_SRG");
	test_fir_srg test_FIR_SRG("TEST_FIR_SRG");

	// connect to module
	u_FIR_SRG.clk(clk);
	u_FIR_SRG.rst(rst);
	u_FIR_SRG.x(x_in);
	u_FIR_SRG.y(y_in);

	// connect to testbench
	test_FIR_SRG.clk(clk);
	test_FIR_SRG.rst(rst);
	test_FIR_SRG.x(x_in);
	test_FIR_SRG.y(y_in);

	// start simulation
	/*sc_start(10, SC_NS);
	rst.write(1);*/

	sc_start(25, SC_NS);
	rst.write(0);


	/*sc_start(25, SC_NS);
	rst.write(1);*/

	sc_start();

	return 0;
}