#include <iostream>
#include <vector>
#include <cmath>
#include <getopt.h>

using namespace std;

enum options { QUEENS };
static struct option command_options[] = {
    {"queens", required_argument, NULL, QUEENS},
    {0, 0, 0, 0}
};

bool conflict(vector<int> queen_positions, int current_position, int n) {
    for (auto& pos : queen_positions) {
        if (abs(pos - current_position) % n == 0)
            return true;
        if (abs(pos/n - current_position/n) == abs(pos % n - current_position % n))
            return true;
    }
    return false;
}

vector<int> find_queen_positions_helper(int n, int queens_remaining, vector<int> queen_positions, int current_position) {
    if (queens_remaining == 0)
        return queen_positions;
    if (current_position == (queens_remaining * n))
        return vector<int>();
    if (conflict(queen_positions, current_position, n)) {
        return find_queen_positions_helper(n, queens_remaining, queen_positions, current_position + 1);
    } else {
        queen_positions.push_back(current_position);
        vector<int> child = find_queen_positions_helper(n, queens_remaining - 1, queen_positions, (queens_remaining-2)*n);
        if (child.empty()) {
            queen_positions.pop_back();
            return find_queen_positions_helper(n, queens_remaining, queen_positions, current_position + 1);
        }
        return child;
    }
}

vector<int> find_queen_positions(int n) {
    vector<int> results;
    if (n <= 0 || n == 2 || n == 3)
        return results;
    return find_queen_positions_helper(n, n, vector<int>(), (n-1)*n);
}

int parse_args(int argc, char* argv[]) {
    int n_queens = -1;
    while (1) {
        int c = getopt_long(argc, argv, "", command_options, NULL);
        if (c == -1) break;
        switch (c) {
            case options::QUEENS:
                n_queens = atoi(optarg);
                break;
        
            default:
                break;
        }
    }
    return n_queens;
}

void print_board(vector<int> queens, int n) {
    vector<char> board;
    int current_queen_pos = 0;
    for (int i = n*n-1; i >= 0; i--) {
        if (queens[current_queen_pos] == i) {
            board.push_back('Q');
            if (current_queen_pos != n-1)
                current_queen_pos++;
        } else
            board.push_back(' ');
    }
    for (int i = 0; i < n*4+1; i++)
        cout << "-";
    cout << "\n";
    for (int i = 1; i <= board.size(); i++) {
        if (i % n == 1)
            cout << "|";
        cout << " " << board[i-1] << " |";
        if (i % n == 0) {
            cout << "\n";
            for (int j = 0; j < n*4+1; j++)
                cout << "-";
            cout << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    int n_queens = parse_args(argc, argv);
    print_board(find_queen_positions(n_queens), n_queens);
}