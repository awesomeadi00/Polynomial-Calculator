#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <exception>
#include <string>

#include "linkedlist.h"
#include "polycalculator.h"
using namespace std;

//Function that displays all of the commands that the user can type.
void listCommands() {
    cout << "List of available Commands:" << endl
            << "display              : Display the Polynomials (Linked Lists)" << endl
            << "input                : Input Polynomial expressions from keyboard" << endl
            << "add                  : Add the Polynomials (Linked Lists)" << endl
            << "sub                  : Subtract the Polynomials (Linked Lists)" << endl
            << "mul                  : Multiply the polynomials (Linked Lists)" << endl
            << "read <file_name>     : Load the data from <file> and add it into the Linked Lists" << endl
            << "write <file_name>    : Dump the contents of the resultant Linked list to a <file>" << endl
            << "help                 : Display the list of available commands" << endl
            << "exit                 : Exit the Program" << endl;
}


int main() {
    //bruh
    PolyCalculator polycalc;
    listCommands();
    string user_input;
    string command;
    string parameter;
    
    do {
        cout << endl;
        cout << ">";
        getline(cin, user_input);
            
        //Parse userinput into command and parameter(s)
        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,parameter);
        
        //Conditional statements, if the user types a specific command, it should call the necessary methods. If they don't enter the correct command, then it is invalid. 
        if(command =="display") {polycalc.display(); }
        else if(command == "input") {polycalc.input(); }
        else if(command == "add") {polycalc.add(); }
        else if(command == "sub") {polycalc.sub(); }
        else if(command == "mul") {polycalc.mul(); }
        else if(command =="read") {polycalc.readData(parameter); }
        else if(command == "write") {polycalc.writeData(parameter); }
        else if(command == "help") {listCommands(); }
        else if(command == "exit" or command== "quit") {break; }
        
        else
            cout<<"Invalid Command!!"<<endl;
        
        fflush(stdin);
        }
    while(true);

    return EXIT_SUCCESS;
}

