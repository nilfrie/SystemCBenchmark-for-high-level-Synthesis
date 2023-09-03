//
// Implementation of the behaviour of the testbench for magnitude.
//

#include "tb_magnitude.h"

//
// Send data to thread
//
void test_magnitude::send() {
	// Variables used for incoming data
	int indatax, indatay;

	// Check File
	errno_t err = fopen_s(&in_file_x, XINFILENAME, "rt");
	if (err)
	{
		cout << "Could not open file " << XINFILENAME << endl;
		sc_stop();
		exit(EXIT_FAILURE);
	}

	errno_t err2 = fopen_s(&in_file_y, YINFILENAME, "rt");
	if (err2)
	{
		cout << "Could not open file " << YINFILENAME << endl;
		sc_stop();
		exit(EXIT_FAILURE);
	}

	wait();

	while (true)
	{
		while ((fscanf_s(in_file_y, "%i", &indatay) != EOF) && (fscanf_s(in_file_x, "%i", &indatax) != EOF))
		{
			y.write(indatay);
			x.write(indatax);
			wait();
		}

		fclose(in_file_x);
		fclose(in_file_y);

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
void test_magnitude::recv() {
	// variables used
	int outdatar;

	// check for the output files
	errno_t err = fopen_s(&out_file_r, ROUTFILENAME, "wt");
	if (err)
	{
		sc_stop();
		exit(EXIT_FAILURE);
	}

	wait();
	wait();
	wait();
	wait();

	while (true) {
		outdatar = r.read();
		fprintf(out_file_r, "%i ", outdatar);

		wait();
	}
}

void test_magnitude::compare() {
	int outr, outexpr, errors = 0;

	fclose(out_file_r);

	errno_t err0 = fopen_s(&out_file_r, ROUTFILENAME, "rt");
	errno_t err1 = fopen_s(&exp_file_r, EXPRFILENAME, "rt");
	if (err0 || err1) {
		sc_stop();
		exit(EXIT_FAILURE);
	}

	while ((fscanf_s(out_file_r, "%i", &outr) != EOF) && (fscanf_s(exp_file_r, "%i", &outexpr) != EOF)) {
		if (outr != outexpr) errors++;
	}

	fclose(out_file_r);
	fclose(exp_file_r);

	if (errors == 0) {
		cout << "All values match the expected values! Tests Successfull!" << endl;
	}
	else {
		cout << "There were " << errors << " mismatches between expected and actaul values running the tests!" << endl;
	}
}