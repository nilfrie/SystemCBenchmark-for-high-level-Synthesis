/*
* Header file to define the behaviour of the testbench for the arctan module.
*/

#include "define.h"

#ifndef TEST_ARCTAN_H
#define TEST_ARCTAN_H

SC_MODULE(test_arctan) {
	// define Inputs 

	sc_in_clk tb_clk;
	sc_in<bool> tb_rst;

	// as out in the testbench

	sc_out<sc_int<W>> tb_x_in;

	//define outputs as in in the testbench

	sc_in<sc_int<W>> tb_f_out;

	// File for data usage
	FILE* in_file_x, * out_file_f, * exp_file;

	// Methods

	void recv();

	void send();

	void compare();

	SC_CTOR(test_arctan) {
		SC_CTHREAD(recv, tb_clk.pos());

		SC_CTHREAD(send, tb_clk.pos());
	};
};

#endif // !TEST_ARCTAN_H
