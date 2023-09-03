/*
* Implementation of module magnitude.
*/

#include "magnitude.h"

void magnitude::control() {
	if (rst) {
		x_r.write(0);
		y_r.write(0);
	}

	wait();

	while (true) {
		if (!rst) {
			x_r.write(x_in.read());
			y_r.write(y_in.read());
		}
		wait();
	}
}

void magnitude::absolute() {
	ax = (x_r.read() >= 0) ? ((int) x_r.read()) : ((int) -x_r.read());
	ay = (y_r.read() >= 0) ? ((int) y_r.read()) : ((int) -y_r.read());

	if (ax > ay) {
		mi = ay;
		ma = ax;
	}
	else {
		mi = ax;
		ma = ay;
	}
}

void magnitude::assignR() {
	if (rst) {
		r_out.write(0);
	}

	wait();

	while (true) {
		if (!rst) {
			r_out.write(ma + mi / 4);
		}
		wait();
	}
}