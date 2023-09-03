//
// Definition file for FIR_GEN module
//

#ifndef DEFINE_FIR_GEN_H
#define DEFINE_FIR_GEN_H

#include "systemc.h"

#include <iostream>
#include "stdio.h"

const int W1 = 9;			// Input bit width
const int W2 = 18;			// Multiplier bit width 2*W1
const int W3 = 19;			// Adder width = W2+log2(L)-1
const int W4 = 11;			// Output bit width
const int L = 4;			// Filter length

#define XINFILENAME             "fir_gen_xinput.txt"
#define OUTFILENAME             "fir_gen_output.txt"
#define CINFILENAME				"fir_gen_cinput.txt"
#define EXPFILENAME				"fir_gen_expect.txt"


#endif  // end DEFINE_FIR_SRG_H