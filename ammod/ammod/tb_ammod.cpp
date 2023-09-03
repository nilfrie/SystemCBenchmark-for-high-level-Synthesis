/*
* Implementation of the behaviour of the testbench for ammod.
*/

#include "tb_ammod.h"

/// Send Data to Thread
void test_ammod::send() {
	// Incoming Data
	int indatar, indataphi;

	// check file
	errno_t err = fopen_s(&in_file_r, RINFILENAME, "rt");
	if (err)
	{
		cout << "Could not open file " << RINFILENAME << endl;
		sc_stop();
		exit(EXIT_FAILURE);
	}

	errno_t err1 = fopen_s(&in_file_phi, PHIINFILENAME, "rt");
	if (err1)
	{
		cout << "Could not open file " << PHIINFILENAME << endl;
		sc_stop();
		exit(EXIT_FAILURE);
	}

	wait();

	while (true) {
		while ((fscanf_s(in_file_r, "%i", &indatar) != EOF) && (fscanf_s(in_file_phi, "%i", &indataphi) != EOF)) {
			tb_r_in.write(indatar);
			tb_phi_in.write(indataphi);
			wait();
			wait();
		}

		fclose(in_file_r);
		fclose(in_file_phi);

		wait();
		wait();
		wait();
		wait();
		wait();

		compare_result();

		sc_stop();

		wait();
	}
}


/// Receive Data from Thread
void test_ammod::recv() {

	// Variable to receive Data
	int outdatax, outdatay, outdataeps;

	// check for the output files
	errno_t err = fopen_s(&out_file_x, XOUTFILENAME, "wt");
	if (err)
	{
		sc_stop();
		exit(EXIT_FAILURE);
	}

	errno_t err1 = fopen_s(&out_file_y, YOUTFILENAME, "wt");
	if (err1)
	{
		sc_stop();
		exit(EXIT_FAILURE);
	}

	errno_t err2 = fopen_s(&out_file_eps, EPSOUTFILENAME, "wt");
	if (err2)
	{
		sc_stop();
		exit(EXIT_FAILURE);
	}

	wait();
	wait();
	wait();
	wait();
	wait();
	wait();

	while (true) {
		wait();

		outdatax = tb_x_out.read();
		outdatay = tb_y_out.read();
		outdataeps = tb_eps_out.read();

		fprintf(out_file_x, "%i ", outdatax);
		fprintf(out_file_y, "%i ", outdatay);
		fprintf(out_file_eps, "%i ", outdataeps);

		//wait();
		wait();
	}
}

void test_ammod::compare_result() {
	int outy, outyexp, outx, outxexp, outeps, outepsexp, errors = 0;

	fclose(out_file_x);
	fclose(out_file_y);
	fclose(out_file_eps);

	errno_t err = fopen_s(&out_file_y, YOUTFILENAME, "rt");
	if (err) {
		sc_stop();
		exit(EXIT_FAILURE);
	}

	errno_t err1 = fopen_s(&exp_file_y, EXPECTEDYFILENAME, "rt");
	if (err1) {
		sc_stop();
		exit(EXIT_FAILURE);
	}

	// Start to compare the results with the expected results of Y
	while ((fscanf_s(exp_file_y, "%i", &outyexp) != EOF) && (fscanf_s(out_file_y, "%i", &outy) != EOF)) {
		if (outyexp != outy) errors++;
	}

	fclose(out_file_y);
	fclose(exp_file_y);

	errno_t err2 = fopen_s(&out_file_x, XOUTFILENAME, "rt");
	if (err2) {
		sc_stop();
		exit(EXIT_FAILURE);
	}

	errno_t err3 = fopen_s(&exp_file_x, EXPECTEDXFILENAME, "rt");
	if (err3) {
		sc_stop();
		exit(EXIT_FAILURE);
	}

	// Start to compare the results with the expected results of X
	while ((fscanf_s(exp_file_x, "%i", &outxexp) != EOF) && (fscanf_s(out_file_x, "%i", &outx) != EOF)) {
		if (outxexp != outx) errors++;
	}

	fclose(out_file_x);
	fclose(exp_file_x);

	errno_t err4 = fopen_s(&out_file_eps, EPSOUTFILENAME, "rt");
	if (err4) {
		sc_stop();
		exit(EXIT_FAILURE);
	}

	errno_t err5 = fopen_s(&exp_file_eps, EXPECTEDEPSFILENAME, "rt");
	if (err5) {
		sc_stop();
		exit(EXIT_FAILURE);
	}

	// Start to compare the results with the expected results of Y
	while ((fscanf_s(exp_file_eps, "%i", &outepsexp) != EOF) && (fscanf_s(out_file_eps, "%i", &outeps) != EOF)) {
		if (outepsexp != outeps) errors++;
	}

	fclose(out_file_eps);
	fclose(exp_file_eps);

	if (errors == 0) {
		cout << "All values match the expected values! Test Successfull!" << endl;
	}
	else {
		cout << "There were " << errors << " mismatches between expected and actaul values running the tests!" << endl;
	}
}