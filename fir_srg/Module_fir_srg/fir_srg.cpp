//
// File Name	: fir_srg.cpp
// 
// Implementation of fir_srg Module.
//


#include "fir_srg.h"

void fir_srg::run()
{
	// Tapped delay line array of bytes
	sc_int<8> tap[4];
	int i = 0;

	// initialize tap
	for (i = 0; i <= 3; i++) tap[i] = 0;

	// wait for clock signal
	wait();

	while (true)
	{

		if (rst)
		{
			for (i = 0; i <= 3; i++) tap[i] = 0;
			y.write(0);
		}
		else if (!rst)
		{
			tap[0] = x.read();
			y.write((tap[1] << 1) + tap[1] + (tap[1] >> 1) - tap[0]
				+ (tap[1] >> 2) + (tap[2] << 1) + tap[2]
				+ (tap[2] >> 1) + (tap[2] >> 2) - tap[3]);


			for (i = 3; i > 0; i--) tap[i] = tap[i - 1];
		}
		wait();
	}
}