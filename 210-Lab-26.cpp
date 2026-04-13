// COMSC-210 | Lab 26 | Joaquin Felix

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <chrono>
using namespace std;

// Named constants
const string FILE_NAME = "names.txt";
const int NUM_OPERATIONS = 4;
const int NUM_STRUCTURES = 3;

// Function prototypes
vector<string> load_names();

int main()
{
    vector<string> names = load_names();

    if (names.size() == 0)
    {
        cout << "ERROR: Could not load names file.\n";
        return 1;
    }

    
    const int NUM_RUNS = 15;
    int results[2][4][3] = {0};

    for (int run = 0; run < NUM_RUNS; run++){
        vector<string> v;
        list<string> l;
        set<string> s;

        // =========================
        // READ
        // =========================

        auto start = chrono::high_resolution_clock::now();

        for (string name : names)
            v.push_back(name);

        auto end = chrono::high_resolution_clock::now();
        results[0][0][0] = chrono::duration_cast<chrono::microseconds>(end - start).count();
        results[1][0][0] += results[0][0][0];

        start = chrono::high_resolution_clock::now();

        for (string name : names)
            l.push_back(name);

        end = chrono::high_resolution_clock::now();
        results[0][0][1] = chrono::duration_cast<chrono::microseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();

        for (string name : names)
            s.insert(name);

        end = chrono::high_resolution_clock::now();
        results[0][2] = chrono::duration_cast<chrono::microseconds>(end - start).count();
    }

    // =========================
    // SORT
    // =========================

    start = chrono::high_resolution_clock::now();

    sort(v.begin(), v.end());

    end = chrono::high_resolution_clock::now();
    results[1][0] = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::high_resolution_clock::now();

    l.sort();

    end = chrono::high_resolution_clock::now();
    results[1][1] = chrono::duration_cast<chrono::microseconds>(end - start).count();

    results[1][2] = -1; // set is already sorted

    // =========================
    // INSERT
    // =========================

    start = chrono::high_resolution_clock::now();

    v.push_back("Zelda");

    end = chrono::high_resolution_clock::now();
    results[2][0] = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::high_resolution_clock::now();

    l.push_back("Zelda");

    end = chrono::high_resolution_clock::now();
    results[2][1] = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::high_resolution_clock::now();

    s.insert("Zelda");

    end = chrono::high_resolution_clock::now();
    results[2][2] = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // =========================
    // DELETE
    // =========================

    start = chrono::high_resolution_clock::now();

    v.pop_back();

    end = chrono::high_resolution_clock::now();
    results[3][0] = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::high_resolution_clock::now();

    l.pop_back();

    end = chrono::high_resolution_clock::now();
    results[3][1] = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::high_resolution_clock::now();

    s.erase("Zelda");

    end = chrono::high_resolution_clock::now();
    results[3][2] = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // =========================
    // OUTPUT
    // =========================

    cout << " Operation    Vector      List       Set\n";
    cout << "      Read"
         << setw(10) << results[0][0]
         << setw(10) << results[0][1]
         << setw(10) << results[0][2] << endl;

    cout << "      Sort"
         << setw(10) << results[1][0]
         << setw(10) << results[1][1]
         << setw(10) << results[1][2] << endl;

    cout << "    Insert"
         << setw(10) << results[2][0]
         << setw(10) << results[2][1]
         << setw(10) << results[2][2] << endl;

    cout << "    Delete"
         << setw(10) << results[3][0]
         << setw(10) << results[3][1]
         << setw(10) << results[3][2] << endl;

    return 0;
}

// load_names() reads names from file
// arguments: none
// returns: vector<string>
vector<string> load_names()
{
    vector<string> names;
    ifstream infile(FILE_NAME);

    if (!infile)
    {
        cout << "ERROR: Could not open " << FILE_NAME << endl;
        return names;
    }

    string name;

    while (infile >> name)
    {
        names.push_back(name);
    }

    infile.close();
    return names;
}