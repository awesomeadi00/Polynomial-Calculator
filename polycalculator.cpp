#include "polycalculator.h"
#include "linkedlist.h"

//================================================================================================================
//Takes the string (Polynomial) and parses the insert function into a LinkedList
void PolyCalculator::parse(string pol, LinkedList& list) {
    stringstream sstr(pol); //when sstr reads (>>), it means that peek() will look at the one after the one read.
    int coef(1), expo;
    char temp;
    
    while(isdigit(sstr.peek()) or isalpha(sstr.peek()) or sstr.peek() == '+' or sstr.peek() == '-') {
        
         //This checks, if there's a plus, if there's a digit after then read, else assign coef = 1
        if(sstr.peek() == '+') {
            sstr >> temp;
            if(sstr.peek() == ' ') {
                cout << "Ensure there are no spaces in your input." << endl;
                break;
            }
            else if(isdigit(sstr.peek())) {
                sstr >> coef;
            }
            else {
                coef = 1;
            }
        }
        
        //This checks, if there's a minus, if there's a digit after then read, else assign coef = -1
        else if(sstr.peek() == '-') {
            sstr >> temp;
            if(sstr.peek() == ' ') {
                cout << "Ensure there are no spaces in your input." << endl;
                break;
            }
            else if(isdigit(sstr.peek())) {
                sstr >> coef;
                coef = coef*-1; //Needs to be negative
            }
            else {
                coef = -1;
            }
        }
        
        //This checks, if there's a digit, just read
        else if(isdigit(sstr.peek())) {
            sstr >> coef;
        }
        
        //This ensures if there is no other value other than x, then there is an invalid input.
        else if(sstr.peek() != 'x') {
            cout << "Invalid Input! Variable used must be 'x' (no spaces either)." << endl;
            break;
        }
        
    //========================
    //After reading coef above, now we read exponents. This checks if the next is 'x'. If it is, read into temp.
        if(sstr.peek() == 'x') {
            if(sstr.fail()) {
                perror("");
                break;
            }
            sstr >> temp;
            
            //If the next after x is '^', it implies an exponent is present. Hence we read ^ into temp.
            if(sstr.peek() == '^') {
                if(sstr.fail()) {
                    perror("");
                    break;
                }
                
                sstr >> temp;
                //Check, if there is no digit after the ^ (cannot have x^x), it is invalid.
                if(!isdigit(sstr.peek())){
                    cout << "Invalid Input! Exponent can only have numbers, no other characters (no spaces)." << endl;
                    break;
                }
                
                else //Read the exponent integer
                    sstr >> expo;
                //Checks, if there is an alphabet after the integer exponent (cannot have x^5x), it is invalid.
                if(isalpha(sstr.peek()) or sstr.peek() == ' ' or sstr.peek() == '^') {
                        cout << "Invalid Input! Exponent can only have numbers, no other characters (no spaces)." << endl;
                        break;
                    }
            }
            
            //Checks, if there is a digit after 'x' (cannot have x5), it is invalid.
            else if(isdigit(sstr.peek())) {
                cout << "Invalid Input! Cannot have integer after 'x'." << endl;
                break;
            }
            
            else if(sstr.peek() == ' ') {
                cout << "Ensure there are no spaces in your input." << endl;
                break;
            }
            
            //If no exponent (^), then the exponent is 1 (as in just x)
            else {expo = 1; }
        }
        
        //Checks, if there is a ^ after a digit (cannot have 5^5), it is invalid.
        else if(sstr.peek() == '^') {
            cout << "Invalid Input! Constants cannot have '^' !" << endl;
            break;
        }
        
        else if(sstr.peek() == ' ') {
            cout << "Ensure there are no spaces in your input." << endl;
            break;
        }
        
        //Else, the exponent is 0 by default (constant)
        else {expo = 0; }
        
        //At this point, coef and expo have values, therefore, insert is called to insert into list.
        list.insert(coef, expo);
    }
}

//================================================================================================================
//Asks the user to input the value of the first and second polynomial. Both inputs must be valid.
void PolyCalculator::input() {
    
    string pol1, pol2;
    //Checks if the lists are empty, if not, remove all the nodes to ensure scratch lists.
    if(!exp1.empty() && !exp2.empty()){
        exp1.removeAll();
        exp2.removeAll();
    }
    
    //Enter first polynomial and parse it into a linked list (list 1)
    cout << "Enter the first polynomial: ";
    cin >> pol1;
    parse(pol1, exp1);
    
    if(!exp1.empty()) {
        //Enter second polynomial and parse it into a linked list (list 2)
        cout << "Enter the second polynomial: ";
        cin >> pol2;
        parse(pol2, exp2);
    }
    
    
    cout << endl;
    display(); //Displays Expression 1 and Expression 2.
    
}

//================================================================================================================
//This function will add both polynomials in list 1 and list 2 together and output it in list 3.
void PolyCalculator::add() {
    
    //Checks if the list is empty, if not, remove all the nodes to ensure scratch list.
    if(!add_list.empty()){
        add_list.removeAll();
    }
    
    //Compares the nodes in list 1 and list 2, if the expo are the same, add both coef and insert into list 3, else just increment till the end of the lists.
    Node *search1 = exp1.head;
    Node *search2 = exp2.head;
    Node *search3;
    int coef, expo;
    
    while(search1 != NULL) {
        while(search2 != NULL) {
            if(search1->expo == search2->expo) {
                coef = search1->coef + search2->coef;
                expo = search1->expo;
                //if the coef == 0 here, then add expo to an array(zero) then break;
                add_list.insert(coef, expo);
                break;
            }
        
            else
                search2 = search2->next;
        }
        search1 = search1->next;
        search2 = exp2.head;
    }
    
    //========================
    //Checks, if there are nodes with exponents not in list 3 from list 2 then add them.
    search2 = exp2.head;
    search3 = add_list.head;
    while(search2 != NULL) {
        while(true) {
            if(search3 == NULL) {
                coef = search2->coef;
                expo = search2->expo;
                //check, if expo is in the array(zero), if so then break, else insert
                add_list.insert(coef, expo);
                break;
            }
            
            else if(search3->expo == search2->expo) {
                break;
            }
            search3 = search3->next;
        }
        search2 = search2->next;
        search3 = add_list.head;
    }
   

    //========================
    //Checks, if there are nodes with exponents not in list 3 from list 1 then add them.
    search1 = exp1.head;
    search3 = add_list.head;
    while(search1 != NULL) {
        while(true) {
            if(search3 == NULL) {
                coef = search1->coef;
                expo = search1->expo;
                //check, if expo is in the array(zero), if so then break, else insert
                add_list.insert(coef, expo);
                break;
            }
            
            else if(search3->expo == search1->expo) {
                break;
            }
            search3 = search3->next;
        }
        search1 = search1->next;
        search3 = add_list.head;
    }
    
    cout << "Exp 1 + Exp 2 = ";
    add_list.display(); //This displays list 3 (added list).
}

//================================================================================================================
//This function will subtract the polynomial in list 2 from list 1 output it in list 3.
void PolyCalculator::sub() {
    
    //Checks if the list is empty, if not, remove all the nodes to ensure scratch list.
    if(!sub_list.empty()){
        sub_list.removeAll();
    }
    
    //Compares the nodes in list 1 and list 2, if the expo are the same, subtract coef from list 2 from coef of list 1 and insert into list 3, else just increment till the end of the lists.
    Node *search1 = exp1.head;
    Node *search2 = exp2.head;
    Node *search3;
    int coef, expo;
    
    while(search1 != NULL) {
        while(search2 != NULL) {
            if(search1->expo == search2->expo) {
                coef = search1->coef - search2->coef;
                expo = search1->expo;
                //if the coef == 0 here, then add expo to an array(zero) then break;
                sub_list.insert(coef, expo);
                break;
            }
            
            else
                search2 = search2->next;
        }
        search1 = search1->next;
        search2 = exp2.head;
    }
    
    //========================
    //Checks, if there are nodes with exponents not in list 3 from list 2 then add them.
    search2 = exp2.head;
    search3 = sub_list.head;
    while(search2 != NULL) {
        while(true) {
            if(search3 == NULL) {
                coef = search2->coef;
                expo = search2->expo;
                //check, if expo is in the array(zero), if so then break, else insert
                sub_list.insert(coef, expo);
                break;
            }
            
            else if(search3->expo == search2->expo) {
                break;
            }
            search3 = search3->next;
        }
        search2 = search2->next;
        search3 = sub_list.head;
    }
    
    //========================
    //Checks, if there are nodes with exponents not in list 3 from list 1 then add them.
    search1 = exp1.head;
    search3 = sub_list.head;
    while(search1 != NULL) {
        while(true) {
            if(search3 == NULL) {
                coef = search1->coef;
                expo = search1->expo;
                //check, if expo is in the array(zero), if so then break, else insert
                sub_list.insert(coef, expo);
                break;
            }
            
            else if(search3->expo == search1->expo) {
                break;
            }
            search3 = search3->next;
        }
        search1 = search1->next;
        search3 = sub_list.head;
    }
    
    cout << "Exp 1 - Exp2 = ";
    sub_list.display(); //This displays list 3 (subtracted list).
}

//================================================================================================================
//This function will multiply both the polynomials in list 1 and list 2 and output it in list 3.
void PolyCalculator::mul() {
    
    //Checks if the list is empty, if not, remove all the nodes to ensure scratch list.
    if(!mul_list.empty()){
        mul_list.removeAll();
    }
    
    //For every node in list 1, multiply that node with every node in list 2, then increment to the next node in list 1 and repeat the process until it reaches the end of the list. For each node multiplied, add it to list 3.
    Node *search1 = exp1.head;
    Node *search2 = exp2.head;
    int coef, expo;

    while(search1 != NULL) {
        while(search2 != NULL) {
            coef = search1->coef * search2->coef;
            expo = search1->expo + search2->expo;
            mul_list.insert(coef, expo);
            search2 = search2->next;
        }
        search1 = search1->next;
        search2 = exp2.head;
    }
    
    cout << "Exp 1 * Exp 2 = ";
    mul_list.display(); //This displays list 3 (multiplied list).
}

//================================================================================================================
//This function will read the polynomials from the file declared by the user, input it into strings, then parse into linked lists and execute the 3 operations (addition, subtraction and multiplication) and then display.
void PolyCalculator::readData(string file) {
    
    //Checks if the lists are empty, if not, remove all the nodes to ensure scratch lists.
    if(!exp1.empty() && !exp2.empty()){
        exp1.removeAll();
        exp2.removeAll();
    }

    //Creates the ifstream (reading a file)
    ifstream inFile;
    inFile.open(file);
    if(inFile.fail()) {
        cout << "Error! File could not be opened!" << endl;
    }
    
    else{
        //Read the exponents into string variables and then parse the strings into linked lists.
        string pol1, pol2;
        inFile >> pol1;
        inFile >> pol2;
    
        parse(pol1, exp1);
        parse(pol2, exp2);
    
        //Displays the expressions, then executes the add, sub, mult and displays the result.
        display();
        cout << "Exp1 + Exp2 = ";
        add();
    
        cout << "Exp1 - Exp2 = ";
        sub();
    
        cout << "Exp1 * Exp2 = ";
        mul();
    }
    
    
    inFile.close(); //Closes the file stream.
}

//================================================================================================================
//This function simply displays polynomial 1 and polynomial 2.
void PolyCalculator::display() {
    cout << "Exp1: ";
    exp1.display(); //Calls list.display() from the linkedlist class functions
    cout << "Exp2: ";
    exp2.display(); //Calls list.display() from the linkedlist class functions
}

//================================================================================================================
//This function will write the inputted polynomials into the file declared by the user. It will take the linked lists and convert them to strings through the "write" function them and write these strings onto the file with the executed operations (add, sub, mul). It also displays the result on the Terminal to show the user whether it is correct or not.
void PolyCalculator::writeData(string file) {
    
    //Creates the ofstream (writing a file)
    ofstream outFile;
    outFile.open(file);
    if(outFile.fail()) {
        cout << "Error! File could not be opened!" << endl;
    }
    else {
        cout << "File written successfully!" << endl;
        cout << "Written the following on the file: " << endl;
        cout << endl;
    
     
        outFile << "Exp 1: ";
        write(exp1, outFile); //Writes out Polynomial 1 onto the file.
    
        outFile << "Exp 2: ";
        write(exp2, outFile); //Writes out Polynomial 2 onto the file.
    
        display();
    
        outFile << "Exp 1 + Exp 2: ";
        add();
        write(add_list, outFile); //Writes out the addition of Pol1 and Pol2 onto the file.
   
        outFile << "Exp 1 - Exp 2: ";
        sub();
        write(sub_list, outFile); //Writes out the subtraction of Pol1 and Pol2 onto the file.
    
        outFile << "Exp 1 * Exp 2: ";
        mul();
        write(mul_list, outFile); //Writes out the multiplication of Pol1 and Pol2 onto the file.
    }      
    
    outFile.close(); //Closes the outFile stream.
}

//================================================================================================================
//This function essentially takes the linked list and converts it into a string and this string will be written through the passed ofstream. Hence it writes it onto the ofstream file. It has the same structure as the display function in LinkedList class method. 
void PolyCalculator::write(LinkedList& list, ofstream& outFile) {
    Node *dis = list.head;
    
    if(dis == NULL) {
        outFile << "No Polynomial!";
        }
    
    else {
            while(dis != NULL) {
    
                if(dis->expo > 1) {
                    if(dis->coef < 0) {
                        outFile << " " << to_string(dis->coef) << "x^" << to_string(dis->expo);
                    }
                    
                    else {
                        outFile << " +" << to_string(dis->coef) << "x^" << to_string(dis->expo);
                    }
                }
                
                else if(dis->expo == 1) {
                    if(dis->coef < 0) {
                        outFile << " " << to_string(dis->coef) << "x";
                    }
                    
                    else {
                        outFile << " +" << dis->coef << "x";
                    }
                }
                
                else if(dis->expo == 0) {
                    if(dis->coef < 0) {
                        outFile << " " << to_string(dis->coef);
                    }
                    
                    else {
                        outFile << " +" << to_string(dis->coef);
                    }
                }
                dis = dis->next;
            }
        }
    outFile << endl;
}
