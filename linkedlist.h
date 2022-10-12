#include <iostream>
#include <string>

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
using namespace std;

//This class represents a single Node in a Singly Linked List
class Node {
private:
    int coef; //Coefficient of a term
    int expo; //Exponent of a term
    Node* next; //Link (pointer) to the next Node
    
public:
    Node(int coef, int expo) : coef(coef), expo(expo), next(NULL) {} //Initializer constructor for the node through initalizing coef and expo.
    friend class LinkedList; //Allows LinkedList class to access Node private members.
    friend class PolyCalculator; //Allows PolyCalculator class to access Node private members.
};

//This class represents a Linked List (contains nodes)
class LinkedList {
private:
    Node* head; //Pointer to the head of the Singly Linked list

public:
    LinkedList (); //Constructor for Linked List, assigns head->NULL.
    ~LinkedList (); // Destructor for Linked Lists (cleans up all the nodes)
    void addFront(int coef, int expo); //Helper function: Adds an new node (with coef, expo) to the front of the Linked List.
    void insert(int coef, int expo); //Inserts a node into the Linked List (simplifies and sorts the polynomial)
    void removeAll(); //Removes all the nodes in the Linked List.
    void display() const; //Displays the polynomial of the Linked List.
    bool empty() const; //Returns true if the Linked List is empty.
    friend class PolyCalculator; //Allows Polycalculator class to access LinkedList private members (head).
};

#endif
