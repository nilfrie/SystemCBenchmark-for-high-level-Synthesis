//
//  Implementation of module fir4dlms.
//

#include "fir4dlms.h"

void fir4dlms::store() {

	int buffer;
	if (rst) {
		for (int k = 0; k <= 2; k++) {
			d[k] = (0);
		}
		for (int i = 0; i <= 4; i++) {
			x[i] = (0);
		}
		for (int i = 0; i <= 1; i++) {
			f[i] = (0);
		}
	}

	wait();

	while (true) {
		if (!rst) {
			d[2] = (d[1]);
			d[1] = (d[0]);
			d[0] = (d_in.read());

			for (int i = 4; i > 0; i--) {
				x[i] = (x[i - 1]);
			}
			x[0] = (x_in.read());

			buffer = xemu[0];
			buffer = buffer >> ((W2 / 2)); // we only want the first half bit from left to right
			f[0] = (f[0] + buffer);
			f0_buf.write(f[0]);

			buffer = xemu[1];
			buffer = buffer >> ((W2 / 2)); // we only want the first half bit from left to right
			f[1] = (f[1] + buffer);
			f1_buf.write(f[1]);
		}
		wait();
	}
}

void fir4dlms::mul() {
	if (rst) {
		for (int i = 0; i < L; i++) {
			p[i] = (0);
			xemu[i] = (0);
		}
		y.write(0);
		e.write(0);
	}

	wait();

	while (true) {
		if (!rst) {

			for (int i = 0; i < L; i++) {
				p[i] = (x[i] * f[i]);
				xemu[i] = (emu * x[i + 3]);
			}
			y.write(p[0] + p[1]);
			e.write(d[2] - ((p[0] + p[1]) >> 8));
		}
		wait();
	}
}

void fir4dlms::assignEmu() {
	emu = (e.read() >> 1);
}

void fir4dlms::assignYOUT() {
	y_out.write(y.read() >> 7);
}

void fir4dlms::assignEOUT() {
	e_out.write(e.read());
}

void fir4dlms::assignF0OUT() {
	f0_out.write(f0_buf.read());
}

void fir4dlms::assignF1OUT() {
	f1_out.write(f1_buf.read());
}