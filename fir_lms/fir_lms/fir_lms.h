//
//	Declaration for the fir_lms module.
//

#include "define.h"

#ifndef FIR_LMS_H
#define FIR_LMS_H

SC_MODULE(fir_lms)
{
	// Define Inputs
	sc_in_clk clk;					// system clock
	sc_in<bool> rst;
	sc_in<sc_int<W1>> x_in;		// system input
	sc_in<sc_int<W1>> d_in;		// reference input

	// Define Output
	sc_out<sc_int<W2>> y_out;	// system output
	sc_out<sc_int<W1>> f0_out;	// 1.filter coefficient
	sc_out<sc_int<W1>> f1_out;	// 2.filter coefficient
	sc_out<sc_int<W2>> e_out;	// error signal

	// Define global Variables
	// Data array
	sc_signal<sc_int<W1>> x[2];

	// Coefficient Array
	sc_signal<sc_int<W1>> f[2];
	sc_signal < sc_int<W1>> d;
	sc_signal < sc_int<W1>> emu;

	// 1. Product array
	sc_signal<sc_int<W2>> p[2];

	// 2. product array
	sc_signal<sc_int<W2>> xemu[2];

	sc_signal<sc_int<W2>> y, sxty, e, sxtd;


	// Declare Methods

	// Runner Method
	void store();

	void mulGen1();

	void assignY();

	void mulGen2();

	void assignE();

	void assignEmu();

	void assignYOUT();

	void assignEOUT();

	void assignF0OUT();

	void assignF1OUT();

	SC_CTOR(fir_lms)
	{
		SC_METHOD(mulGen1);
		sensitive << x[0] << x[1] << f[0] << f[1];

		SC_METHOD(assignY);
		sensitive << p[0] << p[1];

		SC_METHOD(mulGen2);
		sensitive << emu << x[0] << x[1];

		SC_METHOD(assignE);
		sensitive << d << y;

		SC_METHOD(assignEmu);
		sensitive << e;

		SC_METHOD(assignYOUT);
		sensitive << y;

		SC_METHOD(assignEOUT);
		sensitive << e;

		SC_METHOD(assignF0OUT);
		sensitive << f[0];

		SC_METHOD(assignF1OUT);
		sensitive << f[1];

		SC_CTHREAD(store, clk.pos());
		reset_signal_is(rst, true);
	};

	~fir_lms() {};
};


#endif