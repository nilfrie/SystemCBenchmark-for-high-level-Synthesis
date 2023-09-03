/*
* Implementation of the behaviour of the testbench for cordic.
*/

#include "tb_cordic.h"


/// Send Data to Thread
void test_cordic::send() {
	// Incoming Data
	int indatax, indatay;

	// check file
	errno_t err = fopen_s(&in_file_x, XINFILENAME, "rt");
	if (err)
	{
		cout << "Could not open file " << XINFILENAME << endl;
		sc_stop();
		exit(EXIT_FAILURE);
	}

	errno_t err1 = fopen_s(&in_file_y, YINFILENAME, "rt");
	if (err1)
	{
		cout << "Could not open file " << YINFILENAME << endl;
		sc_stop();
		exit(EXIT_FAILURE);
	}

	wait();

	while (true) {
		while ((fscanf_s(in_file_x, "%i", &indatax) != EOF) && (fscanf_s(in_file_y, "%i", &indatay) != EOF)) {
			tb_x_in.write(indatax);
			tb_y_in.write(indatay);
			wait();
		}

		fclose(in_file_x);
		fclose(in_file_y);

		wait();
		compare();
		sc_stop();

		wait();
	}
}

/// Receive Data from Thread
void test_cordic::recv() {

	// Variable to receive Data
	int outdatar, outdataphi, outdataeps;

	// check for the output files
	errno_t err = fopen_s(&out_file_r, ROUTFILENAME, "wt");
	if (err)
	{
		sc_stop();
		exit(EXIT_FAILURE);
	}

	errno_t err1 = fopen_s(&out_file_phi, PHIOUTFILENAME, "wt");
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

	while (true) {

		outdatar = tb_r_out.read();
		outdataphi = tb_phi_out.read();
		outdataeps = tb_eps_out.read();

		fprintf(out_file_r, "%i ", outdatar);
		fprintf(out_file_phi, "%i ", outdataphi);
		fprintf(out_file_eps, "%i ", outdataeps);

		wait();
	}
}

void test_cordic::compare() {

	int outr, outrexp, outphi, outphiexp, outeps, outepsexp, errors = 0;

	fclose(out_file_eps);
	fclose(out_file_phi);
	fclose(out_file_r);

	errno_t err = fopen_s(&out_file_eps, EPSOUTFILENAME, "rt");
	errno_t err1 = fopen_s(&out_file_phi, PHIOUTFILENAME, "rt");
	errno_t err2 = fopen_s(&out_file_r, ROUTFILENAME, "rt");
	errno_t err3 = fopen_s(&exp_file_eps, EPSEXPFILENAME, "rt");
	errno_t err4 = fopen_s(&exp_file_phi, PHIEXPFILENAME, "rt");
	errno_t err5 = fopen_s(&exp_file_r, REXPFILENAME, "rt");
	if (err || err1 || err2 || err3 || err4 || err5) {
		sc_stop();
		exit(EXIT_FAILURE);
	}

	// compare eps
	while ((fscanf_s(exp_file_eps, "%i", &outepsexp) != EOF) && (fscanf_s(out_file_eps, "%i", &outeps) != EOF)) {
		if (outepsexp != outeps) errors++;
	}

	//compare phi
	while ((fscanf_s(exp_file_phi, "%i", &outphiexp) != EOF) && (fscanf_s(out_file_phi, "%i", &outphi) != EOF)) {
		if (outphiexp != outphi) errors++;
	}

	//compare r
	while ((fscanf_s(exp_file_r, "%i", &outrexp) != EOF) && (fscanf_s(out_file_r, "%i", &outr) != EOF)) {
		if (outrexp != outr) errors++;
	}

	fclose(out_file_eps);
	fclose(out_file_phi);
	fclose(out_file_r);
	fclose(exp_file_eps);
	fclose(exp_file_phi);
	fclose(exp_file_r);

	if (errors == 0) {
		cout << "All values match the expected values! Test Successfull!" << endl;
	}
	else {
		cout << "There were " << errors << " mismatches between expected and actaul values running the tests!" << endl;
	}
}