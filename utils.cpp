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
            cmdCharCount=-1; // as then cmdCharCount++ will make it 0;
        }
        
        cmdCharCount++;
    }

    string lastToken=cmd.substr(cmdStart); // only insert last token to cmdTokens if it is non-space command 
    if(lastToken.find_first_not_of(' ') != string::npos)
    cmdTokens.push_back(lastToken);

}

bool executeCustomCommand(vector<string> cmdTokens){
    // all custom commands are handled in customCommands.cpp file.(modularity is better)
    return customCommandsHandler(cmdTokens);

}

void executeCommand(vector<string> cmdTokens){
    
    if(executeCustomCommand(cmdTokens)){
        return;
    }

    // aliasChecker - used to alter tokens of cmd if it just an alias to already existing cmd in system
    cmdTokens=aliasChecker(cmdTokens);


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

vector<string> aliasChecker(vector<string> cmdTokens){

    if(cmdTokens[0]=="showfiles"){
        cmdTokens[0]="ls";
        return cmdTokens;

    }

    if(cmdTokens[0]=="showallfiles"){
        cmdTokens[0]="ls";
        cmdTokens.push_back("-latr");
        return cmdTokens;
    }

    if(cmdTokens[0]=="print"){
        cmdTokens[0]="echo";
        return cmdTokens;
    }  

    if(cmdTokens[0]=="create"){
        cmdTokens[0]="touch";
        return cmdTokens;
    } 

    if(cmdTokens[0]=="createfolder"){
        cmdTokens[0]="mkdir";
        return cmdTokens;
    } 

    if(cmdTokens[0]=="copy"){
        cmdTokens[0]="cp";
        if(cmdTokens[2]=="to")
        cmdTokens.erase(cmdTokens.begin()+2);
        else{ // if 3 param is not 'to', we make sure command not found error shows up.
            string commandNotExist="command-not-found-123";
            cmdTokens[0]=commandNotExist; // changing the main cmd token to random string.
            return cmdTokens;
        }
         
        
        return cmdTokens;
    }

    if(cmdTokens[0]=="cut"){
        cmdTokens[0]="mv";
        if(cmdTokens[2]=="paste")
        cmdTokens.erase(cmdTokens.begin()+2);
        else{ // if 3 param is not 'paste', we make sure command not found error shows up.
            string commandNotExist="command-not-found-123";
            cmdTokens[0]=commandNotExist; // changing the main cmd token to random string.
            return cmdTokens;
        }
         
        
        return cmdTokens;
    }



    if(cmdTokens[0]=="delete"){
        cmdTokens[0]="rm";
        return cmdTokens;
    }    

    if(cmdTokens[0]=="deletefolder"){
        cmdTokens[0]="rm";
        
        // reordering the tokens 
        string temp=cmdTokens[1];
        cmdTokens[1]="-rf";
        cmdTokens.push_back(temp);
        
        return cmdTokens;
    } 


    return cmdTokens;

}