//
//	Declaration for the sqrt module.
//

#include "define.h"

#ifndef SQRT_H
#define SQRT_H

SC_MODULE(SQRT) {
	// define inputs

	sc_in_clk clk;
	sc_in<bool> rst;
	sc_in<sc_uint<32>> x_in;
	sc_in<bool> load;

	// define outputs

	sc_out<sc_uint<32>> c_out;			// System output
	sc_out<bool> c_ready;

	// define global variables

	sc_uint<32> x_n;					// Buffer for X
	sc_signal<sc_uint<32>> c_buff;		// Buffer for C
	unsigned int d;						// Check Variable

	int state, n_state;					// variable for the state machine

	unsigned int buffer;

	// define methods

	void assignC();
	

	SC_CTOR(SQRT) {

		SC_CTHREAD(assignC, clk.pos());
		reset_signal_is(rst, true);
	};
	~SQRT() {};
};

#endif // !SQRT_H
