
/*      Executes a program and writes the output to a timestamped file
                Arguments:
                        file_suffix (e.g. <TimeStamp>_hadoop.log)
                        program arguments
*/


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main(int argc, char * argv[]){
        //Check to see if arguments are correct
        if (argc < 2){
                cerr << "Not enough argument!\n";
                exit(1);
        }
        if (strcmp(argv[1], "-h") == 0 ||
            strcmp(argv[1], "help") == 0){
                cout << "Executes a program and writes the output to a timestamped file\n"
                << "The first argument supplied is appended to the file name"
                << "\nUse the sequence \"\\~\" if no file suffix desired"
                << "\nRemaining arguments are the program whose output you want."
                << "\n\tExample:"
                << "\n\t\twrite_to_timestamp \\~ echo \\\"hello world\\\""
                << "\n\t\tWill write to a file with only the current timestamp as a name\n";
                exit(0);
        }


        //make a temporary file with the system date stamp, then open it
        system("date > date.temp");
        ifstream input;
        input.open("date.temp");
        if (!input) {
                cerr << "date.temp failed to open\n";
                exit(1);
        }

        //Write the first 4 words into an ostringstream
        ostringstream o_string;
        string temp;
        for (int i = 0; i < 4; ++i){
                input >> temp;
                o_string << temp;
                if (i && i != 3) o_string << "_";
        }
        string file_name = o_string.str();
        if (strcmp(argv[1], "~") != 0)
                file_name += argv[1];

        // Create a string containing the arguments
        string argument;
        for (int i = 2; i < argc; ++i){
                argument += argv[i];
                argument += " ";
        }
        argument += "> " + file_name;
        cout << argument << endl;
        //      Execute the program
        system(argument.c_str());
}
