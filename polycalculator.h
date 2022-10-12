#ifndef POLYCACLULATOR_H
#define POLYCACLULATOR_H

#include<fstream>
#include<string>
#include<sstream>
#include "linkedlist.h"
using namespace std;

//This class is the Polynomial Calculator class. It contains all the main Polynomial operations and functions.
class PolyCalculator
{
private:
    LinkedList exp1;
    LinkedList exp2;
    LinkedList add_list;
    LinkedList sub_list;
    LinkedList mul_list;

public:
    void input(); //Takes the input the of values of both polynomial expressions.
    void add(); //Adds both polynomials (exp1 and exp2) and saves the result in add_list.
    void sub(); //Subtracts exp2 from exp1 and saves the results in sub_list.
    void mul(); //Multiplies both polynomials (exp1 and exp2) and saves the result in mul_list.
    void readData(string); //Reads a file and loads the data into the linked lists (exp1 and exp2), executes and displays the results of 3 arithmetic operations.
    void writeData(string); //Writes the polynomial expressions and the results of the 3 arithematic operations onto the file.
    void parse(string, LinkedList&); //Parses the string polynomial into a Linked List.
    void display(); //Displays both polynomials (exp1 and exp2)

private:
    void write(LinkedList& ,ofstream&); //Helper function to write a polynomial expression (List) to a file;
};

#endif
