//
//  Implementation of module fir_lms.
//

#include "fir_lms.h"

void fir_lms::store()
{
	// local Variables

	int buffer = 0;

	if (rst)
	{
		d.write(0);
		x[0].write(0);
		x[1].write(0);
		f[0].write(0);
		f[1].write(0);
	}

	wait();

	while (true)
	{
		if (!rst)
		{
			d.write(d_in.read());

			x[1].write(x[0].read());
			x[0].write(x_in.read());

			buffer = xemu[0].read();
			buffer = buffer >> ((W2 / 2)); // we only want the first half bit from left to right
			
			f[0].write(f[0].read() + buffer);

			buffer = xemu[1].read();
			buffer = buffer >> ((W2 / 2)); // we only want the first half bit from left to right
			
			f[1].write(f[1].read() + buffer);
		}
		wait();
	}
}

void fir_lms::mulGen1()
{
	// instantiate L multiplier
	for (int i = 0; i < L; i++)
	{
		p[i].write(x[i].read() * f[i].read());
	}
}

void fir_lms::assignY()
{
	y.write(p[0].read() + p[1].read());
}

void fir_lms::mulGen2()
{
	for (int i = 0; i <= L - 1; i++)
	{
		xemu[i].write(emu.read() * x[i].read());
	}
}

void fir_lms::assignE()
{
	e.write(d.read() - (y.read() >> 7));
}

void fir_lms::assignEmu()
{
	emu.write(e.read() >> 1);
}

void fir_lms::assignYOUT()
{
	y_out.write((y.read() >> 7));
}

void fir_lms::assignEOUT()
{
	e_out.write(e.read());
}

void fir_lms::assignF0OUT()
{
	f0_out.write(f[0].read());
}

void fir_lms::assignF1OUT()
{
	f1_out.write(f[1].read());
}