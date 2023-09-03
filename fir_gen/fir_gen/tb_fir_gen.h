//
//Header file to define the behaviour of the testbench for the srg_gen module.
//

#include "define.h"

#ifndef TEST_FIR_GEN_H
#define TEST_FIR_GEN_H

SC_MODULE(test_fir_gen)
{
	// Inputs
	sc_in_clk clk;
	sc_in<bool> rst;

	// as out cause in Testbench
	sc_out<sc_int<W1>> x;
	sc_out<sc_int<W1>> c;
	sc_out<bool> load_x;

	// Outputs as in cause in testbench
	sc_in<sc_int<W4>> y;

	// Files for data feeding
	FILE* in_file_x, * out_file, * in_file_c, * exp_file_out;

	// Methods
	
	// receive
	void recv();

	// send
	void send();

	void compare();

	SC_CTOR(test_fir_gen)
	{
		SC_CTHREAD(send, clk.pos());

		SC_CTHREAD(recv, clk.pos());
	};

	~test_fir_gen() {};
};

#endif