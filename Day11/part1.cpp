#include <bits/stdc++.h>
using namespace std;
#define ll long long

string inputLine;
vector<string> stones;

string multiplyStrings(string num1,string num2){
    string result;
    ll n1=num1.length(),n2=num2.length();
    vector<ll> resultNum(5*(n1+n2));
    for(ll index1=n1-1;index1>=0;index1--){
        ll d1=num1[index1]-'0';
        ll resultIndex=n1-1-index1;
        ll c=0;
        for(ll index2=n2-1;index2>=0;index2--,resultIndex++){
            ll d2=num2[index2]-'0';
            ll m=d1*d2+c;
            resultNum[resultIndex]+=m%10;
            c=m/10+resultNum[resultIndex]/10;
            resultNum[resultIndex]%=10;
        }
        while(c>0){
            resultNum[resultIndex]+=c;
            c=resultNum[resultIndex]/10;
            resultNum[resultIndex]%=10;
            resultIndex++;
        }
    }
    
    for(ll i=0;i<5*(n1+n2);i++){
        result+=to_string(resultNum[i]);
    }
    
    while(!result.empty() and result.back()=='0'){
        result.pop_back();
    }
    
    reverse(result.begin(),result.end());
    return result;
}

void updateStonesAfterOneBlink(){
    vector<string> updatedStones;
    for(string stone:stones){
        if(stone.length()==1 and stone[0]=='0'){
            updatedStones.push_back("1");
        }
        else if(stone.length()%2==0){
            ll len=stone.length();
            string num1=stone.substr(0,len/2);
            string num2=stone.substr(len/2);
            while(!num2.empty() and num2[0]=='0'){
                num2.erase(num2.begin());
            }
            if(num2.empty()){
                num2="0";
            }
            updatedStones.push_back(num1);
            updatedStones.push_back(num2);
        }
        else{
            updatedStones.push_back(multiplyStrings(stone,"2024"));
        }
    }
    
    stones=updatedStones;
    return ;
}

ll findNumberOfStonesAfterXBlinks(ll iterations){
    for(ll iteration=1;iteration<=iterations;iteration++){
        updateStonesAfterOneBlink();
    }
    return stones.size();
}


void getInput(){
    getline(cin,inputLine);
    ll inputLength=inputLine.length(),index=0;
    while(index<inputLength){
        string curNum;
        while(index<inputLength and isdigit(inputLine[index])){
            curNum+=inputLine[index++];
        }
        stones.push_back(curNum);
        index++;
    }
    return ;
}

int main() {
    getInput();
    cout<<findNumberOfStonesAfterXBlinks(25);
    return 0;
}
