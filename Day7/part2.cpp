#include <bits/stdc++.h>
using namespace std;
#define ll long long

string input;
ll totalSum,resultSum,n;
vector<ll> inputNums;

bool canEvaluateNumsToGivenSum(ll curResult, ll curIndex){
    if(curIndex==n and curResult==totalSum)
        return true;
    if(curIndex>=n or curResult>totalSum)
        return false;
    // add
    bool result1=canEvaluateNumsToGivenSum(curResult+inputNums[curIndex], curIndex+1);
    if(result1==true)
        return result1;
    // multiply
    bool result2=canEvaluateNumsToGivenSum(curResult*inputNums[curIndex], curIndex+1);
    if(result2==true)
        return result2;
    // concatenate
    bool result3=canEvaluateNumsToGivenSum(curResult*pow(10,to_string(inputNums[curIndex]).length())+inputNums[curIndex], curIndex+1);
    return result3;
}

void parseInput(string input){
    ll sz=input.length();
    totalSum=0;
    ll index=0;
    while(index<sz and input[index]!=':')
        totalSum=totalSum*10+(input[index++]-'0');
    index+=2;
    while(index<sz){
        ll curNum=0;
        while(index<sz and isdigit(input[index]))
            curNum=curNum*10+(input[index++]-'0');
        inputNums.push_back(curNum);
        index++;
    }
    n=inputNums.size();
    return ;
}

void getInputAndCalculate(){
    
    while(!cin.eof()){
        inputNums.clear();
        getline(cin,input);
        parseInput(input);
        if(canEvaluateNumsToGivenSum(inputNums[0],1)){
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
