#include <bits/stdc++.h>
using namespace std;
#define ll long long

string inputLine;
vector<ll> initialSecretNums;
ll mod=16777216;
map<string,ll> globalFreq;

ll calculateTheMostBananas(){
    ll maxBananas=0;
    for(auto entry:globalFreq)
        maxBananas=max(maxBananas,entry.second);
    return maxBananas;
}

void transformSecretNumXTimes(ll &currentSecretNum,ll steps){
    vector<ll> lastFiveNums;
    lastFiveNums.push_back(currentSecretNum%10);
    map<string,ll> freq;
    for(ll step=1;step<=steps;step++){
        ll result1=currentSecretNum*64;
        currentSecretNum^=result1;
        currentSecretNum%=mod;
        result1=currentSecretNum/32;
        currentSecretNum^=result1;
        currentSecretNum%=mod;
        result1=currentSecretNum*2048;
        currentSecretNum^=result1;
        currentSecretNum%=mod;
        lastFiveNums.push_back(currentSecretNum%10);
        if(lastFiveNums.size()==5){
            string seq;
            for(ll index=1;index<5;index++)
                seq+=to_string(lastFiveNums[index]-lastFiveNums[index-1])+",";
            lastFiveNums.erase(lastFiveNums.begin());
            if(freq.find(seq)==freq.end()){
                freq[seq]=lastFiveNums.back();
            }
        }
    }
    for(auto entry:freq)
        globalFreq[entry.first]+=entry.second;
    return ;
}

void transformSecretNumsXTimes(ll steps){
    for(auto &currentSecretNum:initialSecretNums){
        transformSecretNumXTimes(currentSecretNum,steps);
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
    cout<<calculateTheMostBananas();
    return 0;
}
