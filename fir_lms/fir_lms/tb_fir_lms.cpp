//
// Implementation of the behaviour of the testbench for fir_lms.
//

#include "tb_fir_lms.h"

//
// Send data to thread
//
void test_fir_lms::send()
{
	// Variables used for incoming data
	int indatax, indatad;


	// Check File
	errno_t err = fopen_s(&in_file_x, XINFILENAME, "rt");
	if (err)
	{
		cout << "Could not open file " << XINFILENAME << endl;
		sc_stop();
		exit(EXIT_FAILURE);
	}

	errno_t err2 = fopen_s(&in_file_d, DINFILENAME, "rt");
	if (err2)
	{
		cout << "Could not open file " << DINFILENAME << endl;
		sc_stop();
		exit(EXIT_FAILURE);
	}

	wait();


	while (true)
	{
		// Read input file C
		while ((fscanf_s(in_file_d, "%i", &indatad) != EOF) && (fscanf_s(in_file_x, "%i", &indatax) != EOF))
		{
			d.write(indatad);
			x.write(indatax);
			wait();
		}

		fclose(in_file_x);
		fclose(in_file_d);

		wait();
		wait();

		compare();

		sc_stop();

		wait();
	}
}

//
// Receive Data Thread
//
void test_fir_lms::recv()
{
	// variables used
	int outdatay, outdataf0, outdataf1, outdatae;

	// check for the output files
	errno_t err = fopen_s(&out_file_y, YOUTFILENAME, "wt");
	if (err)
	{
		sc_stop();
		exit(EXIT_FAILURE);
	}

	errno_t err2 = fopen_s(&out_file_f0, F0OUTFILE, "wt");
	if (err2)
	{
		sc_stop();
		exit(EXIT_FAILURE);
	}

	errno_t err3 = fopen_s(&out_file_f1, F1OUTFILE, "wt");
	if (err3)
	{
		sc_stop();
		exit(EXIT_FAILURE);
	}

	errno_t err4 = fopen_s(&out_file_error, EOUTFILENAME, "wt");
	if (err4)
	{
		sc_stop();
		exit(EXIT_FAILURE);
	}

	wait();
	wait();
	wait();
	wait();

	while (true)
	{
		
		outdatay = y.read();
		fprintf(out_file_y, "%i ", outdatay);

		outdataf0 = f0.read();
		fprintf(out_file_f0, "%i ", outdataf0);

		outdataf1 = f1.read();
		fprintf(out_file_f1, "%i ", outdataf1);

		outdatae = e.read();
		fprintf(out_file_error, "%i ", outdatae);
		
		wait();
	}
}

void test_fir_lms::compare() {
	int outy, outyexp, outf1, outf1exp, outf0, outf0exp, outerr, outerrexp, errors = 0;

	fclose(out_file_error);
	fclose(out_file_f0);
	fclose(out_file_f1);
	fclose(out_file_y);

	errno_t err0 = fopen_s(&exp_file_y, EXPYFILENAME, "rt");
	errno_t err1 = fopen_s(&exp_file_error, EXPERRFILENAME, "rt");
	errno_t err2 = fopen_s(&exp_file_f0, EXPF0FILENAME, "rt");
	errno_t err3 = fopen_s(&exp_file_f1, EXPF1FILENAME, "rt");
	errno_t err4 = fopen_s(&out_file_error, EOUTFILENAME, "rt");
	errno_t err5 = fopen_s(&out_file_f0, F0OUTFILE, "rt");
	errno_t err6 = fopen_s(&out_file_f1, F1OUTFILE, "rt");
	errno_t err7 = fopen_s(&exp_file_y, YOUTFILENAME, "rt");

	if (err0 || err1 || err2 || err3 || err4 || err5 || err6 || err7) {
		sc_stop();
		exit(EXIT_FAILURE);
	}

	while ((fscanf_s(exp_file_y, "%i", &outyexp) != EOF) && (fscanf_s(out_file_y, "%i", &outy) != EOF)) {
		if (outyexp != outy) errors++;
	}

	while ((fscanf_s(exp_file_error, "%i", &outerrexp) != EOF) && (fscanf_s(out_file_error, "%i", &outerr) != EOF)) {
		if (outerrexp != outerr) errors++;
	}

	while ((fscanf_s(exp_file_f0, "%i", &outf0exp) != EOF) && (fscanf_s(out_file_f0, "%i", &outf0) != EOF)) {
		if (outf0exp != outf0) errors++;
	}

	while ((fscanf_s(exp_file_f1, "%i", &outf1exp) != EOF) && (fscanf_s(out_file_f1, "%i", &outf1) != EOF)) {
		if (outf1exp != outf1) errors++;
	}

	fclose(out_file_error);
	fclose(out_file_f0);
	fclose(out_file_f1);
	fclose(out_file_y);
	fclose(exp_file_error);
	fclose(exp_file_f0);
	fclose(exp_file_f1);
	fclose(exp_file_y);

	if (errors == 0) {
		cout << "All values match the expected values! Tests Successfull!" << endl;
	}
	else {
		cout << "There were " << errors << " mismatches between expected and actaul values running the tests!" << endl;
	}
}