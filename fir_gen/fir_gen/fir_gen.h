//
// File Name	: fir_gen.h
// 
// Declaration for the fir_gen module.
// 
// Last Updated	: tbc...
//


#include "define.h"

#ifndef FIR_GEN_H
#define FIR_GEN_H

SC_MODULE(fir_gen)
{
	// Define Inputs
	sc_in_clk clk;
	sc_in<bool> rst;
	sc_in<bool> load_x;
	sc_in<sc_int<W1>> x_in;
	sc_in<sc_int<W1>> c_in;

	// Define Output
	sc_out<sc_int<W4>> y_out;

	// Define global variables
	sc_signal<sc_int<W1>> x;
	sc_signal<sc_int<W3>> buf_a;
	int c[4];
	int p[4];
	int a[4];

	
	// Declare Methods

	void SOP();

	void load();

	void mulGen();

	void assignYOUT();

	SC_CTOR(fir_gen)
	{
		SC_METHOD(mulGen);
		sensitive << x;

		SC_METHOD(assignYOUT);
		sensitive << buf_a;

		SC_CTHREAD(SOP, clk.pos());
		reset_signal_is(rst, true);

		SC_CTHREAD(load, clk.pos());
		reset_signal_is(rst, true);
	};

	~fir_gen() {};
};


#endif