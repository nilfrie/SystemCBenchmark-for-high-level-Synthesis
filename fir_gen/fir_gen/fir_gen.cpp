//
// File Name	: fir_gen.cpp
// 
// Implementation of fir_gen Module.
// 
// Last Update	: tbc
//


#include "fir_gen.h"

void fir_gen::load()
{
	
	if (rst)
	{
		for (int k = 0; k < L; k++)
		{
			c[k] = 0;
		}
		x.write(0);
	}

	// wait for clock signal
	wait();

	while (true)
	{
		// Load Data/Coefficient
		if (!load_x) {
			for (int i = 0; i < 3; i++)
			{
				c[i] = (c[i + 1]);
			}
			c[3] = (c_in.read()); // Store coefficient in register

			
		}
		else {
			x.write(x_in.read()); // One data sample at a time
		}
		wait();
	}
	
}

void fir_gen::SOP() {
	if (rst)
	{
		for (int k = 0; k < L; k = k++)
		{
			a[k] = (0);
		}
	}

	wait();

	while (true)
	{
		if (load_x) {
			// Compute sum-of-products
			a[0] = (p[0] + a[1]);
			a[1] = (p[1] + a[2]);
			a[2] = (p[2] + a[3]);
			a[3] = (p[3]);
			buf_a.write(a[0]);
		}
		wait();
	}
}

void fir_gen::mulGen() {
	for (int i = 0; i < L; i++) {
		p[i] = (x.read() * c[i]);
	}
}

void fir_gen::assignYOUT() {
	
	sc_int<W3> buffer;

	// Shift to only write y from position (W3 -1) to (W3 - W4)
	buffer = a[0];
	buffer = buffer << 1;
	buffer = buffer >> 1;
	buffer = buffer >> ((W3 - 1) - (W3 - W4));


	y_out.write(buffer);
}