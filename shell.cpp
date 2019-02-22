#include"utils.hpp"
#include<iostream>
#include<stdlib.h>
#include<string>
#include<climits>

using namespace std;


int main(){

	//loading config files (not supported in v1.0.0)

	//important variables 
	bool STATUS=true;
	string COMMAND="";
	//shell initialising screen
	initialiseShell();
	

	// shell 
	do{
		cout<<">";
		COMMAND=fetchCommand();

		if(COMMAND.length()){ // only parse command when non empty
			parseCommand(COMMAND);
		}
		
	}while(STATUS);




	// exit action to perform and terminating the shell
    
    return 0;
}