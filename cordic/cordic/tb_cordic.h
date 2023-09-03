/*
* Header file to define the behaviour of the testbench for the cordic module.
*/

#include "define.h"

#ifndef TEST_CORDIC_H
#define TEST_CORDIC_H

SC_MODULE(test_cordic) {
	// define Inputs 

	sc_in_clk tb_clk;
	sc_in<bool> tb_rst;

	// as out in the testbench
	sc_out<sc_int<W>> tb_x_in;
	sc_out<sc_int<W>> tb_y_in;

	//define outputs as in in the testbench

	sc_in<sc_int<W>> tb_r_out;
	sc_in<sc_int<W>> tb_phi_out;
	sc_in<sc_int<W>> tb_eps_out;

	// File for data usage
	FILE* in_file_x, * in_file_y, * out_file_phi, * out_file_eps, * out_file_r, * exp_file_phi, * exp_file_eps, *exp_file_r;

	// Methods

	void recv();

	void send();

	void compare();

	SC_CTOR(test_cordic) {
		SC_CTHREAD(send, tb_clk.pos());
		
		SC_CTHREAD(recv, tb_clk.pos());
	};
};

#endif // !TEST_CORDIC_H
