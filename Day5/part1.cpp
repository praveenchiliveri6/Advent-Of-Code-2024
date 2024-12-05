#include <bits/stdc++.h>
using namespace std;
#define ll long long

bool isValidInputSeq(vector<ll> &inputSeq, unordered_map<string,ll> &cntMap){
    ll n=inputSeq.size();
    for(ll index1=0;index1<n;index1++){
        string num1=to_string(inputSeq[index1]);
        for(ll index2=index1+1;index2<n;index2++){
            string num2=to_string(inputSeq[index2]);
            if(cntMap.find(num1+"|"+num2)==cntMap.end())
                return false;
        }
    }
    return true;
}


void parseInput(string input, vector<ll> &inputSeq){
    ll n=input.length(),index=0;
    while(index<n){
        string curNum;
        while(index<n and isdigit(input[index])){
            curNum+=input[index];
            index++;
        }
        
        inputSeq.push_back(stoi(curNum));
        index++;
    }
    
    return ;
}

int main() {
    string input;
    unordered_map<string,ll> cntMap;
    ll totalSumOfMiddleNum=0;
    while(!cin.eof()){
        cin>>input;
        if(input.find("|")!=string::npos){
            cntMap[input]++;
        }
        else{
            vector<ll> inputSeq;
            parseInput(input,inputSeq);
            ll n=inputSeq.size();
            if(isValidInputSeq(inputSeq,cntMap)){
                totalSumOfMiddleNum+=inputSeq[n/2];
            }
        }
    }
    cout<<totalSumOfMiddleNum<<endl;
    return 0;
}
