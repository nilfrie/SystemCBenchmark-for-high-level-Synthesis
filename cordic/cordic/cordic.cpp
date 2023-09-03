/*
* Implementation of module cordic.
*/

#include "cordic.h"

void Cordic::this_cordic() {
	if (rst) {
		for (int i = 0; i <= 3; i++) {
			x[i] = 0;
			y[i] = 0;
			z[i] = 0;
		}
		r_out.write(0);
		eps_out.write(0);
		phi_out.write(0);
	}

	wait();

	while (true) {
		if (!rst) {
			if (x_in.read() >= 0) {
				x[0] = x_in.read();
				y[0] = y_in.read();
				z[0]= 0;
			}
			else if (y_in.read() >= 0) {
				x[0] = y_in.read();
				y[0] = -x_in.read();
				z[0] = 90;
			}
			else {
				x[0] = -y_in.read();
				y[0] = x_in.read();
				z[0] = -90;
			}

			if (y[0] >= 0) {
				x[1] = x[0] + y[0];
				y[1] = y[0] - x[0];
				z[1] = z[0] + 45;
			}
			else {
				x[1] = x[0] - y[0];
				y[1] = y[0] + x[0];
				z[1] = z[0] - 45;
			}

			if (y[1] >= 0) {
				x[2]= x[1] + (y[1] >> 1);
				y[2] = y[1] - (x[1] >> 1);
				z[2] = z[1] + 26;
			}
			else {
				x[2] = x[1] - (y[1] >> 1);
				y[2] = y[1] + (x[1] >> 1);
				z[2] = z[1] - 26;
			}
			if (y[2] >= 0) {
				x[3] = x[2] + (y[2] >> 2);
				y[3] = y[2] - (x[2] >> 2);
				z[3] = z[2] + 14;
			}
			else {
				x[3] = x[2] - (y[2] >> 2);
				y[3] = y[2] + (x[2] >> 2);
				z[3] = z[2] - 14;
			}
			r_out.write(x[3]);
			phi_out.write(z[3]);
			eps_out.write(y[3]);

		}
		wait();
	}
}