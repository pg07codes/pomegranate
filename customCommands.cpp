#include "customCommands.hpp"

#include<iostream>
#include<vector>
#include<string>
#include <unistd.h> 

using namespace std;

bool customCommandsHandler(vector<string> cmdTokens){


    vector<string> CUSTOM_COMMANDS{ //order of commands is important as it is
                                    //used below in switch
        "help-me",
        "about-the-creator",
        "cd", // unix cd command
        "goto", // alias to cd for kids
        "bye"
        
    };
    int CUSTOM_CMD_NO=-1;

    for(int i=0;i<CUSTOM_COMMANDS.size();i++){
        
        if(cmdTokens[0]==CUSTOM_COMMANDS[i]){
            CUSTOM_CMD_NO=i;
            break;
        }
        
    }

    if(CUSTOM_CMD_NO==-1){
        return false;
    }

    switch(CUSTOM_CMD_NO){
        case 0:
            openHelpMenu();
            return true;
        case 1:
            cout<<"i am pg. Hi\n";
            return true;
        case 2:
            chdir((char *)cmdTokens[1].c_str());
            return true;
        case 3:
            chdir((char *)cmdTokens[1].c_str());
            return true;
        case 4:
            cout<<"GoodBye!\n";
            exit(0);

        default:
            cout<<"some error has occured\n";
            return false;
    }

}


void openHelpMenu(){
    cout<<"help menu here\n";
}
