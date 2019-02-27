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
        "whereami",
        "cd", // this (for some reason) has to be implemented custom or it don't work
        "moveto", 
        "moveup",
        "movetohome",
        "showfiles",
        "showallfiles",
        "print",
        "createfile",
        "createfolder"
        
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

    // SETTING up USER AND HOME_PATH VARIABLE FOR LATER USE.
    const string USER(getenv("USER"));
    const char* HOME_PATH=("/home/"+USER).c_str();

    switch(CUSTOM_CMD_NO){
        case 0:
            openHelpMenu();
            return true;
        case 1:
            printCurrentDir();
            return true;
        case 2:
            chdir((char *)cmdTokens[1].c_str());
            return true;
        case 3:
            chdir((char *)cmdTokens[1].c_str());
            return true;
        case 4:
            chdir((char *)"..");
            return true;
        case 5:
            //char* user = getenv("USER");
            chdir((char*)HOME_PATH);
            return true;
        case 6:
            // as it is just an alias to ls, we return false -> aliasChecker and system will handle it.
            return false;
        case 7:
            // as it is just an alias to ls -latr, we return false -> aliasChecker and system will handle it.
            return false;
        case 8:
            // as it is just an alias to echo , we return false -> aliasChecker and system will handle it.
            return false;
        case 9:
            // as it is just an alias to touch , we return false -> aliasChecker and system will handle it.
            return false;
        case 10:
            // as it is just an alias to mkdir , we return false -> aliasChecker and system will handle it.
            return false;

        default:
            cout<<"some error has occured\n";
            return false;
    }

}


void openHelpMenu(){
    cout<<"help menu here\n";
}
void printCurrentDir(){

    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    cout<<cwd<<endl; 

}
