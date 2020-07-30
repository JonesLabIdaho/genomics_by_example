// RemoveFastaLineBreaks
// In normal fasta format, each record contains line breaks to make it look nice on screen.
// These line breaks are a curse.
// This program removes the curse.
// 
// Contact Adam Jones, adamjones@uidaho.edu.

// Usage:
// -i	Input Filename
// -o	Output Filename
// -h	Help
// no arguments: Interactive

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main( int argc, char* argv[] )
{
	int i;
	string infile_name_string, outfile_name_string;
	char* infile_name;
	char* outfile_name;
	bool interactivemode = false;

	string query;
	string tempstring1, tempstring2;

	if (argc == 1)
	{
		cout << "\n(I)nteractive or (H)elp?\n";
		cin >> query;
		if (query == "H" || query == "h")
		{
			cout << "\nRemoveFastaLineBreaks\n";
			cout << "-i:\tinput file\n";
			cout << "-o:\toutput file\n";
			cout << "no arguments:\tinteractive mode\n";
			return 0;
		}
	}

	if (argc > 1)
	{
		tempstring1 = argv[1];
		if (tempstring1 == "-h" || tempstring1 == "--help")
		{
			cout << "\nRemoveFastaLineBreaks\n";
			cout << "-i:\tinput file\n";
			cout << "-o:\toutput file\n";
			cout << "no arguments:\tinteractive mode\n";
			return 0;
		}
	}

	infile_name_string = "default";
	outfile_name_string = "default";

	infile_name = new char[1000];
	outfile_name = new char[1000];

	for (i = 1; i < argc-1; i++)
	{
		tempstring1 = argv[i];
		tempstring2 = argv[i+1];
		if (tempstring1 == "-i" || tempstring1 == "--in")
			infile_name_string = tempstring2;
		if (tempstring1 == "-o" || tempstring1 == "--out")
			outfile_name_string = tempstring2;
	}

	if (infile_name_string == "default")
	{
		cout << "Fasta Filename:\n";
		cin >> infile_name_string;	
		interactivemode = true;
	}

	if (outfile_name_string == "default")
	{
		cout << "\nOutput Filename:\n";
		cin >> outfile_name_string;
		interactivemode = true;
	}

	for (i = 0; i < static_cast<int>(infile_name_string.length()); i++)
		infile_name[i] = infile_name_string[i];
	infile_name[i] = '\0';

	for (i = 0; i < static_cast<int>(outfile_name_string.length()); i++)
		outfile_name[i] = outfile_name_string[i];
	outfile_name[i] = '\0';

	cout << "\n\nInput File:\t" << infile_name;
	cout << "\nOutput File:\t" << outfile_name;

	if (interactivemode)
	{
		cout << "\n\nProceed? (y to proceed)\n";
		cin >> query;

		if (query != "y" && query != "Y")
		{
			cout << "\n\nEnter an integer to exit!!";
			cin >> i;
			return 0;
		}
	}
	cout << "\n\nProceeding...\n";

	string firstheader;
	string currentheader;
	string nextheader;
	string currentsequence;
	string tempseq;

	bool headerflag;

	ifstream infile;
	ofstream outfile;

	int number_loaded;

	char *line = new char[200001];

	infile.open(infile_name);
	outfile.open(outfile_name);
	

	infile.getline(line,200000);
	if (line[0] == '>')
		firstheader = line;
	else
	{
		cout << "\nFirst Line:\n" << line;
		cout << "\n\nThis is not a fasta file!\n";
		//cout << "\n\nEnter an integer to exit!!";
		//cin >> i;
		return 0;
	}
	
	cout << "\nFirst Header:\n" << firstheader << "\n";
	nextheader = firstheader;

	number_loaded = 0;
	while (!infile.eof())
	{
		currentheader = nextheader;
		headerflag = false;
		currentsequence.clear();
		
		while (!headerflag && !infile.eof())
		{
			infile.getline(line,200000);
			if (line[0] == '>')
			{
				headerflag = true;
				nextheader = line;
			}
			else
			{
				currentsequence = currentsequence + line;
			}
		}
		

		tempseq.clear();
		for (i = 0; i < currentsequence.length(); i++)
		{
			if (currentsequence[i] != '\r' && currentsequence[i] != '\n')
			{
				tempseq = tempseq + currentsequence[i];
			}
		}

		outfile << currentheader << "\n";
		outfile << currentsequence << "\n";

		number_loaded++;

		if (number_loaded % 10000 == 0)
			cout << "\n" << number_loaded << " records processed.";
	} // end of while not eof

	cout << "\n" << number_loaded << " total records.\n";

	infile.close();

	outfile.close();

	cout << "\n\nDone!\n";
	cout << number_loaded << " records processed.\n\n";
	if (interactivemode)
	{
		cout << "Enter an integer to exit.\n";
		cin >> i;
	}

	delete[] line;
	delete[] infile_name;
	delete[] outfile_name;

	//cout << "\n\nEnter an integer to exit!!";
	//cin >> i;

	return 0;
}