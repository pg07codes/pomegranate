#include"utils.hpp"
#include<iostream>
#include<stdlib.h>
#include<string>
#include<climits>
#include<vector>

using namespace std;


int main(){

	//loading config files (not supported in v1.0.0)

	//initialising important variables 
	bool STATUS=true;
	string COMMAND="";
	vector<string> cmdTokens;
	//shell initialising screen
	initialiseShell();
	

	// shell 
	do{
		cout<<">";
		COMMAND=fetchCommand();

		if(COMMAND.length()){ // only parse command when non empty
			parseCommand(COMMAND,cmdTokens);
		}else continue;

		executeCommand(cmdTokens);

	}while(STATUS);




	// exit action to perform and terminating the shell
    
    return 0;
}