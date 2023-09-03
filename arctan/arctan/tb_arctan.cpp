/*
* Implementation of the behaviour of the testbench for arctan.
*/

#include "tb_arctan.h"

/// Send Data to Thread
void test_arctan::send() {
	// Incoming Data
	int indatax;

	// check file
	errno_t err = fopen_s(&in_file_x, XINFILENAME, "rt");
	if (err)
	{
		cout << "Could not open file " << XINFILENAME << endl;
		sc_stop();
		exit(EXIT_FAILURE);
	}

	wait();

	while (true) {
		while (fscanf_s(in_file_x, "%i", &indatax) != EOF) {
			tb_x_in.write(indatax);
			wait();
		}

		fclose(in_file_x);
		wait();

		compare();

		sc_stop();

		wait();
	}
}


/// Receive Data from Thread
void test_arctan::recv() {
	// Variable to receive Data
	int outdataf;

	// check for the output files
	errno_t err = fopen_s(&out_file_f, FOUTFILENAME, "wt");
	if (err)
	{
		sc_stop();
		exit(EXIT_FAILURE);
	}

	wait();
	wait();
	wait();

	while (true) {

		outdataf = tb_f_out.read();

		fprintf(out_file_f, "%i ", outdataf);

		wait();
	}
}

void test_arctan::compare() {
	int out_f, out_exp, errors = 0;

	fclose(out_file_f);

	errno_t err = fopen_s(&out_file_f, FOUTFILENAME, "rt");
	if (err) {
		sc_stop();
		exit(EXIT_FAILURE);
	}

	errno_t err1 = fopen_s(&exp_file, EXPECTEDFILENAME, "rt");
	if (err1) {
		sc_stop();
		exit(EXIT_FAILURE);
	}

	while ((fscanf_s(exp_file, "%i", &out_exp) != EOF) && (fscanf_s(out_file_f, "%i", &out_f) != EOF)) {
		if (out_exp != out_f) errors++;
	}
	fclose(exp_file);
	fclose(out_file_f);

	if (errors == 0) {
		cout << "All values match the expected values! Test Successfull!" << endl;
	}
	else {
		cout << "There were " << errors << " mismatches between expected and actaul values running the tests!" << endl;
	}
}