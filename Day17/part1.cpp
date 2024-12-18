#include <bits/stdc++.h>
using namespace std;
#define ll long long

string inputLine;
ll registerA,registerB,registerC;
vector<ll> instructions;
ll instructionPointer;

ll comboOperand(ll x){
    if(x<=3)
        return x;
    if(x==4)
        return registerA;
    if(x==5)
        return registerB;
    if(x==6)
        return registerC;
    
    return -1;
}

void executeInstruction(ll opCode,ll literal){
    ll num,den;
    switch(opCode){
        case 0:
            num=registerA;
            den=pow(2,comboOperand(literal));
            registerA=num/den;
            break;
        case 1:
            registerB^=literal;
            break;
        case 2:
            registerB=comboOperand(literal)%8;
            break;
        case 3:
            if(registerA==0)
                return ;
            instructionPointer=literal;
            break;
        case 4:
            registerB^=registerC;
            break;
        case 5:
            cout<<comboOperand(literal)%8<<",";
            break;
        case 6:
            num=registerA;
            den=pow(2,comboOperand(literal));
            registerB=num/den;
            break;
        case 7:
            num=registerA;
            den=pow(2,comboOperand(literal));
            registerC=num/den;
            break;
    }
    return ;
}

void executeInstructions(){
    ll totalInstructions=instructions.size();
    while(instructionPointer<totalInstructions){
        ll opCode=instructions[instructionPointer];
        if(opCode==5 and instructionPointer+1 == totalInstructions)
            executeInstruction(opCode,1ll);
        if(instructionPointer+1 == totalInstructions)
            break;
        ll literal=instructions[instructionPointer+1];
        executeInstruction(opCode, literal);
        if(registerA!=0 and opCode==3)
            continue;
        instructionPointer+=2;
    }
}

void parseInstructions(string s){
    ll n=s.length(),index=0;
    while(index<n){
        ll num=0;
        bool flag=false;
        while(index<n and isdigit(s[index])){
            num=num*10+(s[index]-'0');
            index++;
            flag=true;
        }
        if(flag){
            instructions.push_back(num);
        }
        index++;
    }
    
    return ;
}

ll parseInput(string s){
    ll n=s.length(),index=0,num=0;
    while(index<n){
        while(index<n and isdigit(s[index])){
            num=num*10+(s[index]-'0');
            index++;
        }
        index++;
    }
    return num;
}

void getInput(){
    getline(cin,inputLine);
    registerA=parseInput(inputLine);
    getline(cin,inputLine);
    registerB=parseInput(inputLine);
    getline(cin,inputLine);
    registerC=parseInput(inputLine);
    getline(cin,inputLine);
    
    parseInstructions(inputLine);
    
    return ;
}

int main() {
    getInput();
    executeInstructions();
    return 0;
}
