#include <iostream>
#include <getopt.h>
#include <exception>
#include <tuple>
#include <string>
#include <vector>
#include "utilities/Tree.h"

using namespace std;

enum options { LEVELS, VALUES };

static struct option command_options[] = {
    {"levels", required_argument, NULL, options::LEVELS},
    {"values", required_argument, NULL, options::VALUES},
    {0, 0, 0, 0}
};

tuple<vector<int>, vector<int> > parse_args(int argc, char* argv[]) {
    vector<int> levels;
    vector<int> values;
    while (1) {
        int c = getopt_long(argc, argv, "", command_options, NULL);
        if (c == -1) break;
        switch (c) {
            case options::LEVELS: {
                try {
                    while (optind < argc) {
                        if (argv[optind][0] == '-' && argv[optind][1] == '-') {
                            break;
                        }
                        string arg = argv[optind];
                        levels.push_back(stoi(arg));
                        optind++;
                    }
                } catch(exception& e) {
                    cout << "Parsing Error: invalid argument to " << e.what() << endl;
                }
                break;
            }
            case options::VALUES: {
                try {
                    while (optind < argc) {
                        string arg = argv[optind];
                        values.push_back(stoi(arg));
                        optind++;
                    }
                } catch(exception& e) {
                    cout << "Parsing Error: invalid argument to " << e.what() << endl;
                }
                break;
            }
        }
    }
    return make_tuple(levels, values);
}

int main(int argc, char* argv[]) {
    cout << "minimax tester!\n";
    parse_args(argc, argv);
}