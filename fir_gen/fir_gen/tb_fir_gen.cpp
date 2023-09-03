//
// Implementation of the behaviour of the testbench for fir_gen.
//

#include "tb_fir_gen.h"

//
// Send data to thread
//
void test_fir_gen::send()
{
	// Variables used
	int i = 0;
	int indatax, indatac;

	// Check File
	errno_t err = fopen_s(&in_file_x, XINFILENAME, "rt");
	if (err)
	{
		cout << "Could not open file " << XINFILENAME << endl;
		sc_stop();
		exit(EXIT_FAILURE);
	}

	errno_t err2 = fopen_s(&in_file_c, CINFILENAME, "rt");
	if (err2)
	{
		cout << "Could not open file " << CINFILENAME << endl;
		sc_stop();
		exit(EXIT_FAILURE);
	}

	wait();

	while (true)
	{
		load_x.write(false);
		// Read input file C
		while (fscanf_s(in_file_c, "%i", &indatac) != EOF)
		{
			c.write(indatac);
			//cout << "Neuer Wert C! " << indatac << endl;
			wait();
		}

		load_x.write(true);

		// Read input file X
		while (fscanf_s(in_file_x, "%i", &indatax) != EOF)
		{
			x.write(indatax);
			wait();
		}

		fclose(in_file_x);
		fclose(in_file_c);

		wait();

		compare();

		sc_stop();

		wait();
	}
}

//
// Receive Data Thread
//
void test_fir_gen::recv()
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
	wait();
	wait();
	wait();
	wait();

	while (true)
	{
		if (load_x)
		{
			outdata = y.read();
			fprintf(out_file, "%i\n", outdata);
		}
		wait();
	}
}

void test_fir_gen::compare() {
	int out, outexp, errors = 0;

	fclose(out_file);

	errno_t err = fopen_s(&out_file, OUTFILENAME, "rt");
	errno_t err1 = fopen_s(&exp_file_out, EXPFILENAME, "rt");
	if (err || err1) {
		sc_stop();
		exit(EXIT_FAILURE);
	}

	while ((fscanf_s(exp_file_out, "%i", &outexp) != EOF) && (fscanf_s(out_file, "%i", &out) != EOF)) {
		if (outexp != out) errors++;
	}

	fclose(out_file);
	fclose(exp_file_out);

	if (errors == 0) {
		cout << "All values match the expected values! Test Successfull!" << endl;
	}
	else {
		cout << "There were " << errors << " mismatches between expected and actaul values running the tests!" << endl;
	}
}