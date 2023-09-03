//
//	Definition file for fir_lms module
//

#ifndef DEFINE_FIR_LMS_H
#define DEFINE_FIR_LMS_H

#include "systemc.h"

#include <iostream>
#include "stdio.h"

const int W1 = 8;			// Input bit width
const int W2 = 16;			// Multiplier bit width 2*W1
const int L = 2;			// Filter length
const int DELAY = 3;		// Pipeline steps of multiplier

#define XINFILENAME             "fir_lms_xinput.txt"
#define YOUTFILENAME            "fir_lms_youtput.txt"
#define DINFILENAME				"fir_lms_dinput.txt"
#define F0OUTFILE				"fir_lms_f0output.txt"
#define F1OUTFILE				"fir_lms_f1output.txt"
#define EOUTFILENAME			"fir_lms_eoutput.txt"
#define EXPF0FILENAME			"fir_lms_expf0.txt"
#define EXPYFILENAME			"fir_lms_expy.txt"
#define EXPF1FILENAME			"fir_lms_expf1.txt"
#define EXPERRFILENAME			"fir_lms_experr.txt"


#endif  // end DEFINE_FIR_LMS_H