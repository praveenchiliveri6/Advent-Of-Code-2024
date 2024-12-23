#include <bits/stdc++.h>
using namespace std;
#define ll long long

string inputLine;
vector<ll> initialSecretNums;
ll mod=16777216;

ll calculateSumOfFinalSecretNums(){
    ll sum=0;
    for(ll initialSecretNum:initialSecretNums){
        sum+=initialSecretNum;
    }
    return sum;
}

void transformSecretNumsOneTime(){
    for(auto &currentSecretNum:initialSecretNums){
        ll result1=currentSecretNum*64;
        currentSecretNum^=result1;
        currentSecretNum%=mod;
        result1=currentSecretNum/32;
        currentSecretNum^=result1;
        currentSecretNum%=mod;
        result1=currentSecretNum*2048;
        currentSecretNum^=result1;
        currentSecretNum%=mod;
    }
    return ;
}

void transformSecretNumsXTimes(ll steps){
    for(ll step=1;step<=steps;step++){
        transformSecretNumsOneTime();
    }
    return ;
}


void getInput(){
    while(!cin.eof()){
        ll currentSecretNum;
        cin>>currentSecretNum;
        initialSecretNums.push_back(currentSecretNum);
    }
    return ;
}

int main() {
    getInput();
    transformSecretNumsXTimes(2000);
    cout<<calculateSumOfFinalSecretNums();
    return 0;
}
