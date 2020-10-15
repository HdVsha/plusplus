#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//string FindMax(const vector<string>& info) {
////    if (info.size() == 1) return info[0];
////    vector<string> lst;
////    for(int i = 0; i < info.size(); ++i){
////        // строим список всех элементов кроме выбранного
////        vector<string> tmp;
////        for(int j=0; j < info.size(); ++j)
////            if(j!=i)
////                tmp.push_back(info[j]);
////        string stp = FindMax(tmp);
////        string nxt = info[i] + stp;
////        lst.push_back(nxt);
////    };
////    // lst contains all the comb-s of numbers
////    // sorting lst and returning Max
////    sort(lst.begin(), lst.end());
////    return lst[lst.size()-1];
////}
//    for(unsigned int i = info.size()-1; i > 0; i--){
//        for(unsigned int j = 0; j < i; j++){
//            if (info[j+1]+info[j] > info[j] + info[j+1]){
//                string tmp;
//                tmp = info[j];
//                info[j] = info[j+1];
//                info[j+1] = tmp;
//            }
//        }
//    }
//}

bool comp(const string& a,const  string& b){
    return a+b < b+a;
}

int main(){
    ifstream input("number.in");
    ofstream output("number.out");
    vector<string> array;
    string line;
    while (getline(input, line)) {
        array.push_back(line);
    }
    sort(array.rbegin(), array.rend(),comp);
    string result;
    for (const auto& el: array){
        result+=el;
    }
//    string rez = FindMax(array);
    output << result;

    return 0;
}

