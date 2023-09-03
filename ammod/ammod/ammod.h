/*
*  Declaration for the ammod module.
*/

#include "define.h"

#ifndef AMMOD_H
#define AMMOD_H

SC_MODULE(ammod) {
	//define inputs

	sc_in_clk clk;
	sc_in<bool> rst;
	sc_in<sc_int<W + 1>> r_in;		// Radius Input
	sc_in<sc_int<W + 1>> phi_in;	// Phase Input

	// Outputs

	sc_out<sc_int<W + 1>> x_out;	// x or real part output
	sc_out<sc_int<W + 1>> y_out;	// y or imaginery output
	sc_out<sc_int<W + 1>> eps_out;	// Error of results

	// Global Variables

	sc_signal<sc_int<W + 1>> x[4], y[4], z[4];

	// Methods
	/// Implementation of ammod funcionality
	void this_ammod();

	SC_CTOR(ammod) {
		SC_CTHREAD(this_ammod, clk.pos());
		reset_signal_is(rst, true);
	};
	
	~ammod() {};
};

#endif // !AMMOD_H
