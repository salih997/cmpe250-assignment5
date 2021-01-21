/*
Student Name:
Student Number:
Project Number: 5
Compile Status: [SUCCESS/FAIL]
Running Status: [SUCCESS/FAIL]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/

#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

//// (i modified the code in project 4 to build parseInput method)
void parseInput(ifstream& inFile, long long int & N, long long int & M, vector<long long int> & prices){
    string line , tmp;
    getline(inFile,line);
    istringstream linestream(line);
    getline(linestream, tmp, ' ');
    N = stoi(tmp);
    getline (linestream, tmp, ' ');
    M = stoi (tmp);
    getline (inFile, line);
    istringstream linestream1 (line);
    for(int i=0; i<N; i++){
        getline(linestream1, tmp, ' ');
        prices.push_back(stoi(tmp));
    }
    inFile.close();
}

int main(int argc, char* argv[]){

    if(argc != 3){
        cerr << "Run the code with the following command: ./cmpe250-assignment4 [input_file] [output_file]" << endl ;
        return 1;
    }

    ifstream inFile(argv[1]);
    if (!inFile) { // operator! is synonymous to .fail(), checking if there was a failure
        cerr << "There was a problem opening \"" << argv[1] << "\" as input file" << endl;
        return 1;
    }

    ofstream outFile(argv[2]);
    if (!outFile) {
        cerr << "There was a problem opening \"" << argv[2] << "\" as output file" << endl;
        return 1;
    }

    long long int N , M;
    vector<long long int> prices;
    parseInput(inFile,N,M,prices);
    std::sort(prices.begin(),prices.end());


    ////            myTable use bottom up method and keeps (for every k value) prices
    long long int myTable[N+1];
    myTable[0] = 0;
    long long int myPlusTable[N+1];         //// myPlusTable keeps every increment so that we do not need to calculate all increment
    myPlusTable[0] = 0;

    for(long long int K=1; K<=N; K++){
        long long int plus = prices[K-1] + myPlusTable[max(K-M,(long long int)(0))];
        myTable[K] = myTable[K-1] + plus;
        myPlusTable[K] = prices[K-1] + myPlusTable[max(K-M,(long long int)(0))];
    }
    for(int i=1; i<=N; i++){
        outFile<<myTable[i]<<" ";
    }

    return 0;
}
