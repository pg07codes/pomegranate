#include <string>
#include<vector>
//using namespace std; // this should not be used in header files. use std:: operator

void initialiseShell(void);
std::string fetchCommand();

void parseCommand(std::string, std::vector<std::string>&);
void executeCommand(std::vector<std::string>);
bool executeCustomCommand(std::vector<std::string>);
std::vector<std::string> aliasChecker(std::vector<std::string>);