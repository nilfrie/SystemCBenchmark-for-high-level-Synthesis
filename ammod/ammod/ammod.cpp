/*
* Implementation of module ammod.
*/

#include "ammod.h"

void ammod::this_ammod() {
	if (rst) {
		for (int i = 0; i <= 3; i++) {
			x[i].write(0);
			y[i].write(0);
			z[i].write(0);
		}
		x_out.write(0);
		eps_out.write(0);
		y_out.write(0);
	}

	wait();

	while (true) {
		if (!rst) {
			if (phi_in.read() > 90) {
				x[0].write(0);
				y[0].write(r_in.read());
				z[0].write(phi_in.read() - 90);
			}
			else if (phi_in.read() < -90) {
				x[0].write(0);
				y[0].write(-r_in.read());
				z[0].write(phi_in.read() + 90);
			}
			else {
				x[0].write(r_in);
				y[0].write(0);
				z[0].write(phi_in.read());
			}

			if (z[0].read() >= 0) {
				x[1].write(x[0].read() - y[0].read());
				y[1].write(y[0].read() + x[0].read());
				z[1].write(z[0].read() - 45);
			}
			else {
				x[1].write(x[0].read() + y[0].read());
				y[1].write(y[0].read() - x[0].read());
				z[1].write(z[0].read() + 45);
			}

			if (z[1].read() >= 0) {
				x[2].write(x[1].read() - (y[1].read() >> 1));
				y[2].write(y[1].read() + (x[1].read() >> 1));
				z[2].write(z[1].read() - 26);
			}
			else {
				x[2].write(x[1].read() + (y[1].read() >> 1));
				y[2].write(y[1].read() - (x[1].read() >> 1));
				z[2].write(z[1].read() + 26);
			}

			if (z[2].read() >= 0) {
				x[3].write(x[2].read() - (y[2].read() >> 2));
				y[3].write(y[2].read() + (x[2].read() >> 2));
				z[3].write(z[2].read() - 14);
			}
			else {
				x[3].write(x[2].read() + (y[2].read() >> 2));
				y[3].write(y[2].read() - (x[2].read() >> 2));
				z[3].write(z[2].read() + 14);
			}

			x_out.write(x[3].read());
			eps_out.write(z[3].read());
			y_out.write(y[3].read());
		}
		wait();
	}
}