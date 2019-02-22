#include "utils.hpp"
#include <iostream>
#include <unistd.h> 
#include <sys/wait.h>
#include <limits>
#include<vector>

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


void parseCommand(string cmd,vector<string>& cmdTokens){
    cmdTokens.clear();      // emptying tokens if any from previous command
    
    int cmdStart=0,cmdCharCount=0;
    for(int i=0;i<cmd.length();i++){
        
        if(cmd[i]==' '){
            
            string token=cmd.substr(cmdStart,cmdCharCount);
            
            if(token.length()){
                cmdTokens.push_back(token);   
            }
            
            cmdStart=i+1;
            cmdCharCount=-1;
        }
        
        cmdCharCount++;
    }

    cmdTokens.push_back(cmd.substr(cmdStart));

}

void executeCommand(vector<string> cmdTokens){
    
    char *args[2];
    args[0]=(char *)cmdTokens[0].c_str();
    args[1]= NULL;

    pid_t pid=fork();

    if(pid<0){
        cout<<"error forking a new process";
        return;
    }else if(pid==0){
        //in child process
        execvp(args[0],args);

    }else{
        //in parent process


        wait(NULL);
        return ;
    }
}