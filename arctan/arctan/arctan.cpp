/*
* Implementation of module arctan.
*/

#include "arctan.h"

void arctan::write_buff_f() {
	if (rst) {
		x_buffer.write(0);
	}

	wait();

	while (true) {
		if (!rst) {
			x_buffer.write(x_in.read());
		}
		wait();
	}
}

void arctan::compute() {
	d[4] = 1;
	d[3] = (x_buffer.read() * d[4]) / 128;
	d[2] = ((x_buffer.read() * d[3]) / 128) - d[4] - 12;
	d[1] = ((x_buffer.read() * d[2]) / 128) - d[3];
	d[0] = ((x_buffer.read() * d[1]) / 128) - d[2] + 212;
	f_out.write(((x_buffer.read() * d[0]) / 256) - d[1]);
}