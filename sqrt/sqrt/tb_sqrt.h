//
// Header file to define the behaviour of the testbench for the sqrt module.
//

#include "define.h"

#ifndef TEST_SQRT_H
#define TEST_SQRT_H

SC_MODULE(test_sqrt) {
	// define inputs

	sc_in_clk clk;
	sc_in<bool> rst;

	sc_out<sc_uint<32>> x;
	sc_out<bool> tb_load;

	// define outputs

	sc_in<sc_uint<32>> c;

	// define signals for waiting purposes

	sc_in<bool> c_ready;

	// Files for data
	FILE* in_file_x_in, * out_file_c_out, * exp_file_out;

	// Methods

	void recv();

	void send();

	void compare();

	SC_CTOR(test_sqrt) {
		SC_CTHREAD(send, clk.pos());

		SC_CTHREAD(recv, clk.pos());
	};
};
#endif // !TEST_SQRT_H
