//
//	Declaration for the fir4dlms module.
//

#include "define.h"

#ifndef FIR4DLMS_H
#define FIR4DLMS_H

SC_MODULE(fir4dlms) {
	// Define Inputs

	sc_in_clk clk;					// system clock
	sc_in<bool> rst;
	sc_in<sc_int<W1>> x_in;
	sc_in<sc_int<W1>> d_in;

	// Define Outputs

	sc_out<sc_int<W1>> f0_out;
	sc_out<sc_int<W1>> f1_out;
	sc_out<sc_int<W2>> y_out;
	sc_out<sc_int<W2>> e_out;

	// Define global variables

	int x[5];
	int f[2];
	int d[3];		// Desired signal array
	int emu;
	int xemu[2];	// Product Array
	int p[2];
	sc_signal<sc_int<W2>> y, e;
	sc_signal<sc_int<W1>> f1_buf;
	sc_signal<sc_int<W1>> f0_buf;

	// Define Methods

	void store();

	// Instantiate L pipelined multiplier
	void mul();

	void assignEmu();

	void assignYOUT();

	void assignEOUT();

	void assignF0OUT();

	void assignF1OUT();

	SC_CTOR(fir4dlms) {
		SC_CTHREAD(store, clk.pos());
		reset_signal_is(rst, true);

		SC_CTHREAD(mul, clk.pos());
		reset_signal_is(rst, true);

		SC_METHOD(assignEmu);
		sensitive << e;

		SC_METHOD(assignYOUT);
		sensitive << y;

		SC_METHOD(assignEOUT);
		sensitive << e;

		SC_METHOD(assignF0OUT);
		sensitive << f0_buf;

		SC_METHOD(assignF1OUT);
		sensitive << f1_buf;
	};

	~fir4dlms() {};
};

#endif // !FIR4DLMS_H