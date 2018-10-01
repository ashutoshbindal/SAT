#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void split(string str, string splitBy, vector<string>& tokens)
{
    tokens.push_back(str);
    size_t splitAt;
    size_t splitLen = splitBy.size();
    string frag;
    while(true)
    {
        frag = tokens.back();
        splitAt = frag.find(splitBy);
        if(splitAt == string::npos)
        {
            break;
        }
        tokens.back() = frag.substr(0, splitAt);
        tokens.push_back(frag.substr(splitAt+splitLen, frag.size()-(splitAt+splitLen)));
    }
}

int main(int argc, char* argv[]){
    int n, e, k;
    ofstream fout;
    ifstream fin;

    //initialize the value of n,e,k
    //generating the file name
    string graph_file;
    if(argc > 1){
        string fname(argv[1]);
        graph_file = fname;
    }
    else{
        graph_file = "test";
    }
    graph_file = graph_file + ".graph";

    fin.open(graph_file);
    fin>>n>>e>>k;
    fin.close();

    //literal
    // int m[n][k];
    //
    // for(int i=0; i<n; i++){
    //     for(int j=0; j<k; j++){
    //         m[i][j] = 0;
    //     }
    // }

    // //reading form the output file
    string str;

    //generating the file name
    string input_file;
    if(argc > 1){
        string fname(argv[1]);
        input_file = fname;
    }
    else{
        input_file = "test";
    }
    input_file = input_file + ".satoutput";

    fin.open(input_file);
    // getline(fin, str);
    fin>>str;
    //debugging
    // cout<<str<<endl;

    if(str == "SAT"){

        //new method
        int number;
        vector<int> ans_vec[k];

        for(int j=0; j<n; j++){
            for(int i=0; i<k; i++){
                fin>>number;
                if(number>0){
                    // cout<<number<<endl;
                    // number = number - (j*k);
                    ans_vec[i].push_back(j+1);
                }
            }
        }

        // while(getline(fin, str)){
        //     //process the satisfiability
        //     vector<string> temp;
        //     split(str, " ", temp);
        //     temp.pop_back();
        //
        //     //translating the output into matrix
        //     int iter = 0;
        //     for(int i=0; i<n; i++){
        //         for(int j=0; j<k; j++){
        //             string temp_literal = temp[iter];
        //             int lit = stoi(temp_literal);
        //             if(lit > 0){
        //                 m[i][j] = 1;
        //             }
        //
        //             iter++;
        //         }
        //     }
        //     //conditional
        //     break;
        // }

        //writing in the output file
        //generating the file name
        string output_file;
        if(argc > 1){
            string fname(argv[1]);
            output_file = fname;
        }
        else{
            output_file = "test";
        }
        output_file = output_file + ".subgraphs";

        fout.open(output_file, std::ios_base::app);
        // for(int i=1; i<=k; i++){
        //     int node_exist = 0;
        //     for(int j=0; j<n; j++){
        //         if(m[j][i-1] == 1){
        //             node_exist++;
        //         }
        //     }
        //     fout<<"#"<<to_string(i)<<" "<<to_string(node_exist)<<"\n";
        //     bool flag = false;
        //     for(int j=0; j<n; j++){
        //         if(m[j][i-1] == 1){
        //             if(!flag){
        //                 fout<<to_string(j+1);
        //                 flag = true;
        //             }
        //             else{
        //                 fout<<" "<<to_string(j+1);
        //             }
        //         }
        //     }
        //     fout<<"\n";
        // }

        //new method
        for(int i=1; i<=k;i++){
            vector<int> temp_ans = ans_vec[i-1];
            fout<<"#"<<to_string(i)<<" "<<to_string(temp_ans.size())<<"\n";
            bool flag = true;
            for(int j=0; j<temp_ans.size(); j++){
                if(flag){
                    fout<<to_string(temp_ans[j]);
                    flag = false;
                }
                else{
                    fout<<" "<<to_string(temp_ans[j]);
                }
            }
            fout<<"\n";
        }
        fout.close();
    }
    else{
        //generating the file name
        string output_file;
        if(argc > 1){
            string fname(argv[1]);
            output_file = fname;
        }
        else{
            output_file = "test";
        }
        output_file = output_file + ".subgraphs";

        fout.open(output_file, std::ios_base::app);
        fout<<"0\n";
        fout.close();
    }

    fin.close();

    return 0;
}
