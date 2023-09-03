/*
* Header file to define the behaviour of the testbench for the ammod module.
*/

#include "define.h"

#ifndef TEST_AMMOD_H
#define TEST_AMMOD_H

SC_MODULE(test_ammod) {
	// define Inputs 

	sc_in_clk tb_clk;
	sc_in<bool> tb_rst;

	// as out in the testbench
	
	sc_out<sc_int<W + 1>> tb_r_in;
	sc_out<sc_int<W + 1>> tb_phi_in;

	//define outputs as in in the testbench

	sc_in<sc_int<W + 1>> tb_x_out;
	sc_in<sc_int<W + 1>> tb_y_out;
	sc_in<sc_int<W + 1>> tb_eps_out;

	// File for data usage
	FILE* in_file_r, * in_file_phi, * out_file_x, * exp_file_x, * out_file_y, * exp_file_y, * out_file_eps, * exp_file_eps;

	// Methods

	void recv();

	void send();

	void compare_result();

	SC_CTOR(test_ammod) {
		SC_CTHREAD(send, tb_clk.pos());

		SC_CTHREAD(recv, tb_clk.pos());
	};
	
};

#endif // !TEST_AMMOD_H
