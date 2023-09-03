//
// Implementation of the behaviour of the testbench for fir_srg.
//

#include "tb_fir_srg.h"

//
// Send Data Thread
//
void test_fir_srg::send()
{
	// Variables used
	int i = 0;
	int indata;

	// Check File
	errno_t err = fopen_s(&in_file, INFILENAME, "rt");
	if (err)
	{
		cout << "Could not open file " << INFILENAME << endl;
		sc_stop();
		exit(EXIT_FAILURE);
	}

	wait();

	while (true)
	{

		// Read input file
		while (fscanf_s(in_file, "%i", &indata) != EOF)
		{
			x.write(indata);
			wait();
		}

		fclose(in_file);

		wait();

		compare();

		sc_stop();

		wait();
	}
}

//
// Receive Data Thread
//
void test_fir_srg::recv()
{
	// variables used
	int outdata;

	// check for the output file
	errno_t err = fopen_s(&out_file, OUTFILENAME, "wt");
	if (err)
	{
		sc_stop();
		exit(EXIT_FAILURE);
	}

	wait();
	wait();
	wait();

	while (true)
	{
		outdata = y.read();
		fprintf(out_file, "%i\n", outdata);
		
		wait();
	}
}

//
// Comparing results
//
void test_fir_srg::compare()
{
	int out, outexp, errors = 0;

	fclose(out_file);

	errno_t err0 = fopen_s(&out_file, OUTFILENAME, "rt");
	errno_t err1 = fopen_s(&exp_file_out, EXPOUTFILE, "rt");
	if (err0 || err1) {
		sc_stop();
		exit(EXIT_FAILURE);
	}

	while ((fscanf_s(exp_file_out, "%i", &outexp) != EOF) && (fscanf_s(out_file, "%i", &out) != EOF)) {
		if (outexp != out) errors++;
	}

	fclose(out_file);
	fclose(exp_file_out);

	if (errors == 0) {
		cout << "All values match the expected values! Tests Successfull!" << endl;
	}
	else {
		cout << "There were " << errors << " mismatches between expected and actaul values running the tests!" << endl;
	}
}