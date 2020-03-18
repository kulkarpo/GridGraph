#include <unistd.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "core/type.hpp"

using namespace std;

int main(int argc, char ** argv) {
    int opt;
    string input = "";
    string output = "";
    while ((opt = getopt(argc, argv, "i:o:")) != -1) {
        switch (opt) {
        case 'i':
            input = optarg;
            break;
        case 'o':
            output = optarg;
            break;
        }
    }
    if (input=="" || output=="") {
        cerr << "usage: " << argv[0]
                  << " -i [input path] -o [output path]" << endl;
        return -1;
    }

    ifstream fin(input);
    if (!fin) {
        cerr << "Could not open input file '" << input << "'" << endl;
        return 1;
    }

    ofstream fout(output, ios::binary);
    string line;
    while (getline(fin, line)) {
        if (line[0] == '#') continue;
        istringstream sin(line);
        VertexId src, dst;

        sin >> src >> dst;
        fout.write((char*)&src, sizeof(VertexId));
        fout.write((char*)&dst, sizeof(VertexId));
    }

    fout.close();
    fin.close();
    cout << "Convert done" << endl;
    return 0;
}
