#include <bits/stdc++.h>
using namespace std;
#define ll long long

bool isMulEnabled=true;

ll findResult(string &input){
    ll n=input.length(),result=0,index=0;
    
    while(index<n){
        if(index+4<n and input.substr(index,4)=="mul("){
            index+=4;
            
            ll num1=0,num2=0;
            
            while(index<n and isdigit(input[index])){
                num1=num1*10+(input[index]-'0');
                index++;
            }
            
            if(input[index]!=',')
                continue;
                
            index++;
            
            while(index<n and isdigit(input[index])){
                num2=num2*10+(input[index]-'0');
                index++;
            }
            
            if(input[index]!=')')
                continue;
                
            if(isMulEnabled)
                result+=num1*num2;
          
            index++;
        }
        else if(index+7<n and input.substr(index,7)=="don't()"){
            isMulEnabled=false;
            index+=7;
        }
        else if(index+4<n and input.substr(index,4)=="do()"){
            isMulEnabled=true;
            index+=4;
        }
        else{
            index++;
        }
    }
    
    return result;
}

int main() {
    ll result=0;
    while(!cin.eof()){
        string input;
        getline(cin,input);
        result+=findResult(input);
    }
    cout<<result<<endl;
    
    return 0;
}
