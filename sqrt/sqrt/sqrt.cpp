//
//  Implementation of module sqrt.
//

#include "SQRT.h"

void SQRT::assignC() {
	if (rst) {
		c_buff.write(0);
		c_ready.write(0);
		state = s_load;
	}

	wait();

	while (true) {
		if (!rst) {
			switch (state) {
				case s_load: 
					x_n = x_in.read();
					c_buff.write(0);
					d = 1 << 30;
					c_ready.write(0);
					state = s_shift;
					break; 
			
				case s_shift: 
					if (d > x_n) {
						d >>= 2;
						state = s_shift;
					}
					else {
						state = s_calc;
					}
					break;
				case s_calc:
					if (d != 0) {
						if (x_n >= c_buff.read() + d) {
							buffer = c_buff.read() + d;
							x_n = x_n - buffer;
							c_buff.write((c_buff.read() >> 1) + d);
						}
						else {
							c_buff.write(c_buff.read() >> 1);
						}
						d >>= 2;
						state = s_calc;
					}
					else {
						state = s_done;
					}
					break;
				case s_done:
					c_out.write(c_buff.read());
					c_ready.write(1);
					wait();
					state = s_load;
					break;
			}
		}
		wait();
	}
}
