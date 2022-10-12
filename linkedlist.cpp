#include "linkedlist.h"

//================================================================================================================
//Constructor: Empty List constructor
LinkedList::LinkedList() {this->head = NULL; } //points head to NULL

//================================================================================================================
//Destructor: Destructor to clean up all the nodes
LinkedList::~LinkedList() {
    while(!empty()) removeAll(); //Checks while the Lists are not empty, remove all the nodes.
}

//================================================================================================================
//Returns true is the Linked List is empty (Used for destructor)
bool LinkedList::empty() const {
    {return head == NULL; } //Returns true if the head is pointing to NULL - meaning that the list is empty.
}

//================================================================================================================
//Adds a node at the front of the List
void LinkedList::addFront(int coef, int expo) {
    Node *front = new Node(coef, expo); //Creates a new node with coef and expo.
    front->next = head; //New node will point to the front element (what the head is pointing to)
    head = front; //Repoint the head to this new element so now it is the new front.
}

//================================================================================================================
//Add a new Node (term) at the right place in the Linked List. If coef is = 0, then no need to insert into list.
void LinkedList::insert(int coef, int expo) {
    
    //Check, if the list is empty, then add a new node at the front.
    if(head == NULL) {
        addFront(coef, expo);
    }
    
    else if(head != NULL){
        Node *search = head; //search will check is the expo of the new node is the same, less than or greater than the one it is pointing to.
        
        while(search != NULL) {
            //If the expo is the same as the one search is pointing to, it will add the coefficients (simplifies)
            if(expo == search->expo) {
                search->coef += coef;
                break;
            }
            
            //If the expo is greater than the one search is pointing to, it will add to the front (sorts)
            else if(expo > search->expo) {
                addFront(coef, expo);
                break;
            }
            
            //If the expo is less than the one search is pointing to, it will either add to the very back of the list or between two nodes (sorts).
            else if(expo < search->expo) {
                Node *upper = search;
                Node *lower = search->next;
                while(true) {
                    if(lower == NULL) { //Inserts new node to the very back
                        Node *val = new Node(coef, expo);
                        upper->next = val;
                        val->next = lower;
                        break;
                    }
                    
                    else if(expo < upper->expo && expo > lower->expo) { //Inserts new node between two nodes.
                        Node *val = new Node(coef, expo);
                        upper->next = val;
                        val->next = lower;
                        break;
                    }
                    
                    else if(expo == lower->expo) { //If it does equal, then add the coefficients (simplifies)
                        lower->coef += coef;
                        break;
                    }
                    
                    upper = upper->next;
                    lower = lower->next;
                }
                break;
            }
        }
    }
}
    
//================================================================================================================
//This function cleans up (deletes) all of the nodes. It checks if the list is not empty, the recursively remove the front element until the list is empty. If it is not empty, it will print out "No Polynomial"
void LinkedList::removeAll() {
    if(head != NULL) {
        while(head != NULL) {
            Node *old = head;
            head = old->next;
            delete old;
        }
    }
        
    else
        cout << "No Polynomial!" << endl;
}

//================================================================================================================
//This function simply displays the simplified and sorted polynomial.
void LinkedList::display() const {
    Node *dis = head;
    
    //If list is empty, then there is no Polynomial
    if(dis == NULL) {
        cout << "No Polynomial!";
        }
    
    //If it the coef is a negative number, then it will print with the '-' sign because it parsed as a negative integer, but if the coef is a positive number, then it will not print with the '+' sign and it would print just as an int. Hence we print out the '+' manually
    else {
            while(dis != NULL) {
    
                if(dis->expo > 1) { 
                    if(dis->coef < 0) {
                        cout << " " << dis->coef << "x^" << dis->expo;
                    }
                    
                    else {
                        cout << " +" << dis->coef << "x^" << dis->expo;
                    }
                }
                
                else if(dis->expo == 1) {
                    if(dis->coef < 0) {
                        cout << " " << dis->coef << "x";
                    }
                    
                    else {
                        cout << " +" << dis->coef << "x";
                    }
                }
                
                else if(dis->expo == 0) {
                    if(dis->coef < 0) {
                        cout << " " << dis->coef;
                    }
                    
                    else {
                        cout << " +" << dis->coef;
                    }
                }
                dis = dis->next;
            }
        }
    cout << endl;
}
