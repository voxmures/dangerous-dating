#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "Input file not given" << endl;
		return 0;
	}

	const char* input = argv[1];
	string output = "dictionary.h";

	string line;
	ifstream ifile;
	ifile.open(input);
	if (ifile.is_open()) {
		ofstream ofile;
		ofile.open(output.data());

		if (ofile.is_open()) {
			// Write the timestamp
			time_t time = chrono::system_clock::to_time_t(chrono::system_clock::now());
			ofile << "//Generated automatically with ScriptPack 0.1 at " << ctime(&time) << endl;

			// Write the C++ headers
			ofile << "#ifndef DICTIONARY_H\n#define DICTIONARY_H\n" << endl;

			// Write library
			ofile << "const unsigned char library[] PROGMEM = {" << endl;

			vector<int> sentences;
			int idx = 0;
			while (getline(ifile, line)) {
				const char * cline = line.c_str();
				int length = line.length() - 1;

				sentences.push_back(idx);
				idx += length;

				ofile << "\t" << dec << length << ", " << endl;

				ofile << "\t";
				int j = 0;
				for (int i = 0; i <= length; i++) {
					ofile << "0x" << hex << uppercase << (int)cline[i] << ", ";
					if (++j > 7 && i < length) {
						ofile << endl << "\t";
						j = 0;
					}
				}
				ofile << endl;
			}
			ofile << "};" << endl << endl;

			// Write sentences
			ofile << "const unsigned int sentences[] PROGMEM = {" << endl;
			
			ofile << "\t";
			int j = 0;
			for (int i = 0; i < sentences.size(); i++) {
				ofile << dec << sentences[i] << ", ";
				if (++j > 7 && i < sentences.size()) {
					ofile << endl << "\t";
					j = 0;
				}
			}
			ofile << endl << "};" << endl << endl;

			// Write the end of the file
			ofile << "#endif // DICTIONARY_H";

			ofile.close();

		}
		else cout << "Unable to open file: " << output << endl;
		ifile.close();
	}

	else cout << "Unable to open file: " << input << endl;

	return 0;
}