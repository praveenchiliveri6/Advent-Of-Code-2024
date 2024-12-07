#include <bits/stdc++.h>
using namespace std;
#define ll long long

string input;
ll totalSum,resultSum;
vector<ll> inputNums;

bool canEvaluateNumsToGivenSum(ll totalSum,vector<ll> &inputNums){
    ll n=inputNums.size();
    // 0 -> +
    // 1 -> *
    for(ll combination=0;combination<(1ll<<(n-1));combination++){
        ll curEvalSum=inputNums[0];
        for(ll index=0;index<n-1;index++)
            if((combination>>index)&1){
                curEvalSum*=inputNums[index+1];
            }
            else{
                curEvalSum+=inputNums[index+1];
            }
        if(curEvalSum==totalSum){
            return true;
        }
    }
    return false;
}

void parseInput(string input){
    ll n=input.length();
    totalSum=0;
    ll index=0;
    while(index<n and input[index]!=':')
        totalSum=totalSum*10+(input[index++]-'0');
    index+=2;
    while(index<n){
        ll curNum=0;
        while(index<n and isdigit(input[index]))
            curNum=curNum*10+(input[index++]-'0');
        inputNums.push_back(curNum);
        index++;
    }
    
    return ;
}

void getInputAndCalculate(){
    
    while(!cin.eof()){
        inputNums.clear();
        getline(cin,input);
        parseInput(input);
        if(canEvaluateNumsToGivenSum(totalSum, inputNums)){
            resultSum+=totalSum;
        }
    }
}

int main() {
    
    resultSum=0;
    getInputAndCalculate();
    cout<<resultSum;
    return 0;
}
