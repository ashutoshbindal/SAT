#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main(){
    //variable declaration
    int n, e, k;
    vector<pair<int, int>> edge;

    //reading from the file
    ifstream fin;
    fin.open("test.graph");
    fin>>n>>e>>k;

    //checking
    // cout<<n<<" "<<e<<" "<<k<<endl;

    while(!fin.eof()){
        int a, b;
        fin>>a>>b;
        //start the indexing from 0
        a -= 1;
        b -= 1;
        // cout<<a<<" "<<b<<endl;
        pair<int, int> temp;
        temp = {a, b};
        edge.push_back(temp);
    }
    fin.close();

    //remove the last element since it is read twice
    edge.pop_back();

    //just checking the vector
    // for(int i=0; i<edge.size(); i++)
    // {
    //     cout<<edge[i].first<<" "<<edge[i].second<<endl;
    // }

    //literal
    int m[n][k];

    for(int i=0; i<n; i++){
        for(int j=0; j<k; j++){
            m[i][j] = 0;
        }
    }

    //writing into a filename
    ofstream fout;
    fout.open("input.txt", std::ios_base::app);
    fout<<"p cnf # #\n";

    //clause 1: all nodes be present in atleast one subgraph
    for(int i=0; i<n; i++){
        for(int j=0; j<k; j++){
            fout<<to_string(i*k + j+1)<<" ";
        }
        fout<<"0\n";
    }

    //clause 2

    //clause 3

    //clause 4

    fout.close();
}
