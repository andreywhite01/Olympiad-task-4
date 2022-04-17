#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int MakeStep(int prev_step, vector<int> stones, int curr_pos_index, int curr_pos);

int main()
{
    ifstream fin;
    fin.open("input.txt");
    string stones_str;
    vector<int> stones;


    getline(fin, stones_str);
    string::iterator it_start = stones_str.begin();

    while (it_start != stones_str.end()) {
        string::iterator it_end = find(it_start, stones_str.end(), ',');
        int stone = atoi(string(it_start, it_end).c_str());

        if (stone != 0)
            stones.push_back(stone);

        if (it_end != stones_str.end())
            it_start = it_end + 1;
        else
            break;
    }

    int prev_step = 1;
    int current_step = 1;
    int current_step_index = 0;

    ofstream fout;
    fout.open("output.txt");

    if (MakeStep(prev_step, stones, current_step_index, current_step))
        fout << "True";
    else
        fout << "False";
    return 0;
}

int MakeStep(int prev_step, vector<int> stones, int curr_pos_index, int curr_pos) {
    vector<int> possible_steps_length;
    possible_steps_length.push_back(curr_pos + prev_step - 1);
    possible_steps_length.push_back(curr_pos + prev_step);
    possible_steps_length.push_back(curr_pos + prev_step + 1);

    vector<int> possible_steps;

    vector<int>::iterator it = stones.begin() + curr_pos_index + 1;
    for (it; it < stones.end(); it++) {
        for (int i = 0; i < 3; ++i) {
            if ((*it) == possible_steps_length[i]) {
                if ((*it) == (*(stones.end() - 1)))
                    return true;
                possible_steps.push_back((*it));
                break;
            }
        }
    }

    if (possible_steps.size() == 0)
        return false;

    for (int i = 0; i < possible_steps.size(); i++) {

        int stone_index = find(stones.begin(), stones.end(), possible_steps[i]) - stones.begin();
        if (MakeStep(possible_steps[i] - curr_pos, stones, stone_index, possible_steps[i]))
            return true;
        else
            continue;
    }
    return false;
}