#include "utils.hpp"
#include"termcolor.hpp"
#include "customCommands.hpp"

#include <iostream>
#include <unistd.h> 
#include <sys/wait.h>
#include <limits>
#include <vector>
#include<string>

#include<readline/readline.h>
#include<readline/history.h>



using namespace std;

//this function will help us clear console 
#define CLEAR_SCREEN() cout<<"\033[H\033[J" 

void initialiseShell(){
    
    CLEAR_SCREEN();

    //startup welcome screen and logo 
    cout<<termcolor::on_red;
    cout<<" WELCOME TO POMEGRANATE :) \n";
    cout<<termcolor::reset;

    //waiting for user to press enter key
    cout<<"\nPress enter to continue...";
    char x=cin.get();
    
    if(! (x=='\n')){ // discarding the input buffer if any other keys pressed
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }

    CLEAR_SCREEN();

}

string fetchCommand(){

    char* cmd; 
	cmd = readline(" ~~~> "); //reads line and puts to cmd pointer
	if (strlen(cmd) != 0) { // if not empty cmd
		add_history(cmd); //add to command history 
        string cmdString(cmd);// convert char* to std::string;
        return cmdString;//return command string
	}
    return ""; // else return empty command string 
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

bool executeCustomCommand(vector<string> cmdTokens){
    // all custom commands are handled in customCommands.cpp file.(modularity is better)
    return customCommandsHandler(cmdTokens);

}

void executeCommand(vector<string> cmdTokens){
    
    if(executeCustomCommand(cmdTokens)){
        return;
    }
    // var tokenCount is for total token in *args (args[] will be passed to exec)
    int tokenCount=cmdTokens.size() +1; // adding +1 for NULL at last 
    char *args[tokenCount];
    for(int i=0;i<cmdTokens.size();i++){
        args[i]=(char *)cmdTokens[i].c_str();
    }
    args[tokenCount-1]= NULL;

    pid_t pid=fork();

    if(pid<0){
        cout<<"error forking a new process\n";
        return;
    }else if(pid==0){
        //in child process
        if(execvp(args[0],args)<0){
            cout<<"Command not found...\n";
        }

    }else{
        //in parent process


        wait(NULL);
        return ;
    }
}