//
// File Name    : fir_srg.h
//
// Declaration for the fir_srg module.
//

#include "define.h"


#ifndef FIR_SRG_H
#define FIR_SRG_H

SC_MODULE(fir_srg)
{
	// Inputs
	sc_in_clk clk;
	sc_in<bool> rst;
	sc_in<sc_int<8>> x;

	// Outputs
	sc_out<sc_int<8>> y;


	// Methods
	

	/* R */
	void run();


	SC_CTOR(fir_srg)
	{
		SC_CTHREAD(run, clk.pos());
	};

	~fir_srg() {};

};

#endif  // FIR_SRG_H