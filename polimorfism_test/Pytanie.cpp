//
// Created by Magda on 14.04.2023.
//
#include <iostream>
#include "Pytanie.h"
int Pytanie::getBad_Marked() const{
    int n = 0;
    for(auto i : ans){
        if(i==BAD_MARKED) n++;
    }
    return n;
}
int Pytanie::getOK_Marked() const{
    int n = 0;
    for(auto i : ans){
        if(i==OK_MARKED) n++;
    }
    return n;
}
int Pytanie::getBad_Unmarked() const{
    int n = 0;
    for(auto i : ans){
        if(i==BAD_UNMARKED) n++;
    }
    return n;
}
int Pytanie::getOK_Unmarked() const{
    int n = 0;
    for(auto i : ans){
        if(i==OK_UNMARKED) n++;
    }
    return n;
}
int Pytanie::nOfBad() const{
    int n = 0;
    for(auto i : ans){
        if(i==BAD_MARKED || i==BAD_UNMARKED) n++;
    }
    return n;
}
int Pytanie::nOfOk() const{
    int n = 0;
    for(auto i : ans){
        if(i==OK_MARKED || i==OK_UNMARKED) n++;
    }
    return n;
}
int Pytanie::nOfUnmarked() const{
    int n = 0;
    for(auto i : ans){
    if(i==OK_UNMARKED || i==BAD_UNMARKED) n++;
    }
    return n;
}

Pytanie::Pytanie(const std::vector<Odpowiedzi> &ans) : ans(ans) {}
Pytanie::Pytanie(int n){
    for(int i = 0; i < n; i++){
        int a;
        Odpowiedzi answer;
        std::cin >> a;
        if(a == 0) answer = BAD_MARKED;
        else if(a == 1) answer = BAD_UNMARKED;
        else if(a == 2) answer = OK_MARKED;
        else if(a == 3) answer = OK_UNMARKED;
        ans.push_back(answer);
    }
}

int Pytanie::nOfAns() const{
    return ans.size();
}

