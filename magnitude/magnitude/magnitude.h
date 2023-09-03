//
//	Declaration for the magnitude module.
//

#include "define.h"

#ifndef MAGNITUDE_H
#define MAGNITUDE_H

SC_MODULE(magnitude) {
	// define inputs

	sc_in_clk clk;
	sc_in<bool> rst;
	sc_in<sc_int<16>> x_in, y_in;

	// define Outputs

	sc_out<sc_int<16>> r_out;

	// define global variables

	sc_signal<sc_int<16>> x_r, y_r;
	int ax, ay, mi, ma;

	// define methods

	void control();
	void absolute();
	void assignR();

	SC_CTOR(magnitude) {
		SC_CTHREAD(control, clk.pos());
		reset_signal_is(rst, true);

		SC_CTHREAD(assignR, clk.pos());
		reset_signal_is(rst, true);

		SC_METHOD(absolute);
		sensitive << x_r << y_r;
	};
	~magnitude() {};
};

#endif // !MAGNITUDE_H
