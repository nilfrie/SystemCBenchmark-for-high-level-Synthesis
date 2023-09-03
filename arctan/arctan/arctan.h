/*
*  Declaration for the arctan module.
*/

#include "define.h"

#ifndef ARCTAN_H
#define ARCTAN_H

SC_MODULE(arctan) {
	//define inputs

	sc_in_clk clk;
	sc_in<bool> rst;
	sc_in<sc_int<W>> x_in;

	// Outputs

	sc_out<sc_int<W>> f_out;

	// Global Variables

	sc_signal<sc_int<W>> x_buffer;
	int d[5];

	// Methods

	void write_buff_f();

	void compute();

	SC_CTOR(arctan) {
		SC_CTHREAD(write_buff_f, clk.pos());
		reset_signal_is(rst, true);

		SC_METHOD(compute);
		sensitive << x_buffer;
	};

	~arctan() {};
};

#endif // !ARCTAN_H
