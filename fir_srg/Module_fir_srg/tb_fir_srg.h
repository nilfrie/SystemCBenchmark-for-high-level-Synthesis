//
//Header file to define the behaviour of the testbench for the srg_fir module.
//

#include "define.h"


#ifndef TEST_FIR_SRG_H
#define TEST_FIR_SRG_H

SC_MODULE(test_fir_srg)
{
	// Inputs
	sc_in_clk clk;
	sc_in<bool> rst;

	// as out cause in Testbench
	sc_out<sc_int<8>> x;

	// Outputs as in cause in testbench
	sc_in<sc_int<8>> y;

	//For data feeding
	FILE* in_file, * exp_file_out, * out_file;


	// Methods

	/* compare the results */
	void compare();

	/* receive */
	void recv();

	/* S */
	void send();


	SC_CTOR(test_fir_srg)
	{
		SC_CTHREAD(send, clk.pos());

		SC_CTHREAD(recv, clk.pos());
	};

	~test_fir_srg() {};

};

#endif  // TEST_FIR_SRG_H