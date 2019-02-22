#include "utils.hpp"
#include <iostream>
#include <unistd.h> 
#include <limits>
using namespace std;

//this function will help us clear console 
#define CLEAR_SCREEN() cout<<"\033[H\033[J" 

void initialiseShell(){
    
    CLEAR_SCREEN();

    //startup welcome screen and logo 
    cout<<"welcome to pomegranate.\n";

    //waiting for user to press enter key
    cout<<"\nPress Enter To Continue.";
    char x=cin.get();
    
    if(! (x=='\n')){ // discarding the input buffer if any other keys pressed
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }

    CLEAR_SCREEN();

}

string fetchCommand(){
    string cmd;
    getline(cin,cmd);
    return cmd;
}