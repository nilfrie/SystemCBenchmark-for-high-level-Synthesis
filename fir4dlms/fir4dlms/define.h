//
//	Definition file for fir4dlms module
//

#ifndef DEFINE_FIR4DLMS_H
#define DEFINE_FIR4DLMS_H

#include "systemc.h"

#include <iostream>
#include "stdio.h"

const int W1 = 8;			// Input bit width
const int W2 = 16;			// Multiplier bit width 2*W1
const int L = 2;			// Filter length

#define XINFILENAME             "fir4dlms_xinput.txt"
#define YOUTFILENAME            "fir4dlms_youtput.txt"
#define DINFILENAME				"fir4dlms_dinput.txt"
#define F0OUTFILE				"fir4dlms_f0output.txt"
#define F1OUTFILE				"fir4dlms_f1output.txt"
#define EOUTFILENAME			"fir4dlms_eoutput.txt"
#define EXPF0FILENAME			"fir4dlms_expf0.txt"
#define EXPYFILENAME			"fir4dlms_expy.txt"
#define EXPF1FILENAME			"fir4dlms_expf1.txt"
#define EXPERRFILENAME			"fir4dlms_experr.txt"


#endif  // end DEFINE_FIR4DLMS_H