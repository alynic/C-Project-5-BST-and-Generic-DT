

#include "Andrade_h.h"

int main()
{
	ifstream infile;	// Input stream handling variable
	ofstream outfile;	// Output stream handling variable
	CommandType command;	// CommandType class member access variable
	TreeType <int> tree_i;		// Integer binary search tree variable
	TreeType <char> tree_c;		// Character binary search tree variable
	TreeType <string> tree_s;	// String binary search tree variable
	int item_i;		// Variable to store the current integer value being processed
	char item_c;	// Variable to store the current character value being processed
	string item_s;	// Variable to store the current string value being processed
	bool more = false;	// Control structure variable for determining if there is more input
	bool done = false;	// Control structure variable for determining when the data type for the current input file is determined
	bool finished = false;	// Control structure variable for determining when the current operation is finished
	bool completeProgram = false;	// Control structure variable for determining when the current binary search tree is complete
	char datatype;	// Variable for storing the current data type of the items being processed
	int filenum = 1;	// Variable indicating which input and output files to use, according to the indicated data type
	string action;		// Variable that stores the action indicated in the input file
	string infilename;		// Variable to store the current input file name being used
	string outfilename;		// Variable to store the current output file name being used

	while (!completeProgram)
	{
		bool complete = false;	// Control structure variable indicating when the current data type input file is finished being processed

		switch (filenum)
		{
		case 1 : infilename = "test1.in";
				 outfilename = "test1.out";
				 filenum++;
				 break;
		case 2 : infilename = "test2.in";
				 outfilename = "test2.out";
				 filenum++;
				 break;
		case 3 : infilename = "test3.in";
				 outfilename = "test3.out";
				 completeProgram = true;
				 break;
		}// End of switch statement

		infile.open(infilename);

		if (!infile)
		{
			outfile << "Cannot open file.\n\n";
			exit(2);
		}// End of if statement

		outfile.open(outfilename);

		if (infile >> action >> datatype && !done)
		{
			convertAction(action, command, outfile);
			done = true;
		}// End of if statement

		else if (!done)
			break;

		switch (datatype)
		{
		case 'C' : outfile << "-- CPSC 131: Lab#5 Binary Search Tree --";

				   while (!complete)
				   {
					   tree_c.getData(infile, outfile, item_c, datatype, complete, action, command);

					   if (complete)
						   break;

					   tree_c.buildTree(item_c, finished, more, action, command, outfile);
				   }// End of while loop

				   break;
		case 'I' : outfile << "-- CPSC 131: Lab#5 Binary Search Tree --";

				   while (!complete)
				   {
					   tree_i.getData(infile, outfile, item_i, datatype, complete, action, command);

					   if (complete)
						   break;

					   tree_i.buildTree(item_i, finished, more, action, command, outfile);
				   }// End of while loop

				   break;
		case 'S' : outfile << "-- CPSC 131: Lab#5 Binary Search Tree --";

				   while (!complete)
				   {
					   tree_s.getData(infile, outfile, item_s, datatype, complete, action, command);

					   if (complete)
						   break;
					   
					   tree_s.buildTree(item_s, finished, more, action, command, outfile);
				   }// End of while loop

				   break;
		}// End of switch statement

		outfile << "\n\n-- The End of CPSC 131 Lab#5 --";
		done = false;

		infile.close();
		outfile.close();
	}// End of while loop

	return 0;
}// End of main() function