#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) { //constructor
            data = val; 
            prev = p;
            next = n;
        }
    };
    // pointer to first and last node
    Node* head;
    Node* tail;

public:

    //constructor start with empty list
    DoublyLinkedList() { head = nullptr; tail = nullptr; }


    // insert a value after position  insert_after(value, position)
    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl; // if position is less than 0 return
            return;
        }

        Node* newNode = new Node(value); // create new node
        if (!head) {
            // empty list: head and tail point to the new node
            head = tail = newNode;
            return;
        }

        // walk to the node at the position enter
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;// move to right node by i++

        if (!temp) {
            // position is bigger than current size
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;// avoid leak
            return;
        }

        // Link newNode after temp
        newNode->next = temp->next; //newNode points to temp's old next
        newNode->prev = temp;   //newNode points back to temp
        if (temp->next)
            temp->next->prev = newNode;// old next now points to newNode
        else
            tail = newNode;
        temp->next = newNode; // temp now point to newNode
    }



    // delte the node that the data is equal to value
    void delete_val(int value) {
        if (!head) return; //empty list

        //find matching node
        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;//walk right

        if (!temp) return; //if not found
        //link left previous over temp
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            //removing the head
            head = temp->next; 

        //link right next over temp
        if (temp->next)
            temp->next->prev = temp->prev;
        else
            //removing the tail
            tail = temp->prev; 

        delete temp;// free the removed node
    }


    // delete the node at position of the node
    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();// head removal from pop_front
            return;
        }
    

        Node* temp = head;
    //walk to pos of the node
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            //use pop_back to move node
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev; //keep pointer to the prev
        tempPrev->next = temp->next; //keep pointer to the next
        temp->next->prev = tempPrev; //next and prev are now point over temp
        delete temp;//free removed node
    }

    //append new node at the tail
    void push_back(int v) {
        Node* newNode = new Node(v); // new node
        if (!tail)
            //if empty head and tail point to the same
            head = tail = newNode;
        else {
            tail->next = newNode; //old tail point to newnode
            newNode->prev = tail; //new node point to old tail
            tail = newNode; // move newnode to the tail
        }
    }


    //append new node at the head
    void push_front(int v) {
        Node* newNode = new Node(v); 
        if (!head)//if empty head and tail point to the same
            head = tail = newNode;
        else {
            newNode->next = head; //new node point to old head
            head->prev = newNode; //new head point to newnode
            head = newNode; // move head to new node
        }
    }
    
    // remove the head node
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head; // node to delete

        if (head->next) {
            head = head->next; // move head right
            head->prev = nullptr; //new head has no prev
        }
        else
            //removing the only node there
            head = tail = nullptr; // list now is empty
        delete temp;//free old node
    }



     // remove the tail node
    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;// node to delete

        if (tail->prev) {
            tail = tail->prev;// move tail left
            tail->next = nullptr; //new tail has no next
        }
        else
            //removing the only node there
            head = tail = nullptr;// list now is empty
        delete temp;//free old node
    }


    // print the 1st, 3rd, 5th...... node with out modifying the link
    void every_other_element() {
        Node* temp = head;
        cout << "Every other: ";

        bool firstout = true;
        while (temp){
            if(!firstout) cout << " ";
            cout << temp->data; // output the current node data
            firstout = false;

            // if possible move one step
            if (!temp->next) break; //no i+1 we already printed the first one
            temp = temp->next; // move to i+1 but no print

            // if possible again move to the second step
            if (!temp->next) break; // if there are none then don
            temp = temp->next; // move to i+2 this will be printed
        }
        cout << "\n";
    }


    //destructor
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head; // remember current head
            head = head->next; // move head first
            delete temp; //delete the old node
        }
    }

    //print the list from head to tail
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next; // move to the right
        }
        cout << endl;
    }

    //print the list from tail to head
    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev; // move left
        }
        cout << endl;
    }
};

int main() {
    //cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    DoublyLinkedList list;
    DoublyLinkedList empty_ls;
    DoublyLinkedList one_ls;
    DoublyLinkedList two_ls;

    list.push_back(10);
    list.push_back(50);
    list.push_back(60);
    list.push_back(44);
    list.push_back(130);
    list.push_back(770);
    list.push_back(59);
    list.push_back(63);
    // testing when list is empty
    cout<< "Empty "; 
    empty_ls.every_other_element();

    // testing when list is only one item
    one_ls.push_back(936);
    cout<< "One Item "; 
    one_ls.every_other_element();

    // testing when list contains 2 items
    two_ls.push_back(88);
    two_ls.push_back(487);
    cout<< "Two Item "; 
    two_ls.every_other_element();

    cout<< "List print: " ; 
    list.print();
    cout<< "List backward: ";
    list.print_reverse();

    cout<< "\n";

    list.insert_after(99, 1); // after index 1
    cout << "After insert_after(99,1): "; 
    list.print();
    list.delete_val(130); // deleting the value 130
    cout << "After delete_val(130):     "; 
    list.print();

    list.delete_pos(3); //delete at node 3
    cout << "After delete_pos(3):     "; 
    list.print();


    //1st, 3rd, 5th ....
    list.every_other_element();
    
    return 0;
}