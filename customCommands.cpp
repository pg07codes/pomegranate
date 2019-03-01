#include "customCommands.hpp"

#include<iostream>
#include<vector>
#include<string>
#include <unistd.h> 

// curlpp for api data fetching - like jokes, images
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

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
        "create",
        "createfolder",
        "tellmeajoke",
        "tellmeafact",
        "ilovenumbers",
        "whatsmyip",
        "bored",
        "copy",
        "cut",
        "delete",
        "deletefolder"

        
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
        case 11:
            webApiHandler("joke");
            return true;
        case 12:
            webApiHandler("fact");
            return true;
        case 13:
            webApiHandler("number");
            return true;
        case 14:
            webApiHandler("ip");
            return true;
        case 15:
            webApiHandler("bored");
            return true;
        case 16:
            // as it is just an alias to mkdir , we return false -> aliasChecker and system will handle it.
            return false;
        case 17:
            // as it is just an alias to mkdir , we return false -> aliasChecker and system will handle it.
            return false;
        case 18:
            // as it is just an alias to mkdir , we return false -> aliasChecker and system will handle it.
            return false;
        case 19:
            // as it is just an alias to mkdir , we return false -> aliasChecker and system will handle it.
            return false;

        default:
            cout<<"some error has occured\n";
            return false;
    }

}


void openHelpMenu(){
    cout<<"help menu will soon be here.\n";
}
void printCurrentDir(){

    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    cout<<cwd<<endl; 

}

void webApiHandler(string choice){
    
    char* URL=NULL;

    if(choice=="joke")
    URL = (char*)"https://icanhazdadjoke.com/";
    else if(choice=="fact")
    URL = (char*)"http://randomuselessfact.appspot.com/random.txt?language=en";
    else if(choice=="number")
    URL = (char* )"http://numbersapi.com/random";
    else if(choice=="ip")
    URL = (char*)"https://api.ipify.org/";
    else if(choice=="bored")
    URL = (char*)"http://www.boredapi.com/api/activity/";

  
  try {
    
    curlpp::Cleanup cleaner;
    curlpp::Easy request;

    // Setting the URL to retrive.
    curlpp::options::Url myURL(URL);
    request.setOpt(myURL );
    
    // setting http header for Accept text only
    list<string> headers;
	headers.push_back("ACCEPT: text/plain");
    request.setOpt(new curlpp::options::HttpHeader(headers));
    
    cout << request << endl;
  }
  catch ( curlpp::LogicError & e ) { 
      cout<<"Internet seems to be down!"<<endl;
      cout << e.what() << endl;
  }
  catch ( curlpp::RuntimeError & e ) {
      cout<<"Internet seems to be down!"<<endl;
      cout << e.what() << endl;
  }

}
 
