//
// Header file to define the behaviour of the testbench for the fir_lms module.
//

#include "define.h"


#ifndef TEST_FIR_LMS_H
#define TEST_FIR_LMS_H

SC_MODULE(test_fir_lms)
{
	// Inputs
	sc_in_clk clk;
	sc_in<bool> rst;

	// as out cause in Testbench
	sc_out<sc_int<W1>> x;
	sc_out<sc_int<W1>> d;

	// Outputs as in cause in testbench
	sc_in<sc_int<W2>> y;
	sc_in<sc_int<W1>> f0;	// 1.filter coefficient
	sc_in<sc_int<W1>> f1;	// 2.filter coefficient
	sc_in<sc_int<W2>> e;	// error signal

	// Files for data feeding
	FILE* in_file_x, * out_file_y, * in_file_d, * out_file_f0, * out_file_f1, * out_file_error, * exp_file_y, * exp_file_f0, * exp_file_f1, * exp_file_error;

	// Methods

	// receive
	void recv();

	// send
	void send();

	void compare();

	SC_CTOR(test_fir_lms)
	{
		SC_CTHREAD(send, clk.pos());

		SC_CTHREAD(recv, clk.pos());
	};

	~test_fir_lms() {};
};

#endif