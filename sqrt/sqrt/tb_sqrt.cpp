/*
*  Implementation of the behaviour of the testbench for sqrt.
*/

#include "tb_sqrt.h"

/// Send data to thread
void test_sqrt::send() {

	// Variables used for incoming data
	unsigned int indatax;


	// Check File
	errno_t err = fopen_s(&in_file_x_in, XINFILENAME, "rt");
	if (err)
	{
		cout << "Could not open file " << XINFILENAME << endl;
		sc_stop();
		exit(EXIT_FAILURE);
	}

	wait();


	while (true)
	{
		// Read input file C
		while (fscanf_s(in_file_x_in, "%i", &indatax) != EOF)
		{
			x.write(indatax);
			while (c_ready.read() != 1) {
				wait();
			}
			wait();
			wait();
		}

		fclose(in_file_x_in);
		while (c_ready.read() != 1) {
			wait();
		}
		wait();

		compare();

		sc_stop();

		wait();
	}
}


/// Receive Data Thread
void test_sqrt::recv()
{
	// variables used
	unsigned int outdatac, first = 1;

	// check for the output files
	errno_t err = fopen_s(&out_file_c_out, COUTFILENAME, "wt");
	if (err)
	{
		sc_stop();
		exit(EXIT_FAILURE);
	}

	wait();


	while (true)
	{

		while (c_ready.read() != 1) {
			wait();
		}

		outdatac = c.read();
		if (first != 1) {
			fprintf(out_file_c_out, "%i ", outdatac);
		}
		else first = 0;
		
		wait();
		wait();
	}
}

void test_sqrt::compare() {
	int out, expout, errors = 0;

	fclose(out_file_c_out);

	errno_t err0 = fopen_s(&out_file_c_out, COUTFILENAME, "rt");
	errno_t err1 = fopen_s(&exp_file_out, EXPOUTFILENAME, "rt");
	if (err0 || err1) {
		sc_stop();
		exit(EXIT_FAILURE);
	}

	while ((fscanf_s(out_file_c_out, "%i", &out) != EOF) && (fscanf_s(exp_file_out, "%i", &expout) != EOF)) {
		if (out != expout) errors++;
	}

	fclose(out_file_c_out);
	fclose(exp_file_out);

	if (errors == 0) {
		cout << "All values match the expected values! Tests Successfull!" << endl;
	}
	else {
		cout << "There were " << errors << " mismatches between expected and actaul values running the tests!" << endl;
	}
}