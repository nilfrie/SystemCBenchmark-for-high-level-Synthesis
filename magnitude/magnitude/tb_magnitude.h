//
// Header file to define the behaviour of the testbench for the magnitude module.
//

#include "define.h"

#ifndef TEST_MAGNITUDE_H
#define TEST_MAGNITUDE_H

SC_MODULE(test_magnitude) {
	// define inputs

	sc_in_clk clk;
	sc_in<bool> rst;

	// as out cause in Testbench
	sc_out<sc_int<16>> x, y;

	// Outputs as in cause in testbench
	sc_in<sc_int<16>> r;

	// Files for data feeding
	FILE* in_file_x, * in_file_y, * out_file_r, * exp_file_r;

	// Methods

	// receive
	void recv();

	// send
	void send();

	void compare();

	SC_CTOR(test_magnitude) {
		SC_CTHREAD(send, clk.pos());

		SC_CTHREAD(recv, clk.pos());
	};
};

#endif // !TEST_MAGNITUDE_H
