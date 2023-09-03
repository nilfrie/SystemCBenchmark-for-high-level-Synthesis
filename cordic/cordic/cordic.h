/*
*  Declaration for the cordic module.
*/

#include "define.h"

#ifndef CORDIC_H
#define CORDIC_H

SC_MODULE(Cordic) {
	// define inputs

	sc_in_clk clk;
	sc_in<bool> rst;
	sc_in<sc_int<W>> x_in;				// System real or x input
	sc_in<sc_int<W>> y_in;				// System imaginery or y input

	//define outputs

	sc_out<sc_int<W>> r_out;			// Radius result
	sc_out<sc_int<W>> phi_out;			// Phase result
	sc_out<sc_int<W>> eps_out;			// Error of results

	// define global variables

	int x[4], y[4], z[4];

	// define methods

	void this_cordic();

	SC_CTOR(Cordic) {
		SC_CTHREAD(this_cordic, clk.pos());
		reset_signal_is(rst, true);
	};

	~Cordic() {};

};

#endif // !CORDIC_H
