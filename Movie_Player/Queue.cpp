#ifndef QUEUE_CPP
#define QUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated linked list
//Note: Because the linked list is a templated class,
//      there is only ONE file (Queue.cpp)

//Templated node class
template <class T>
class Node {
public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
   return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Queue {
 public:
  // Name: Queue() Queue from a linked list - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new queue where m_head and m_tail
  //                 point to nullptr and m_size = 0
  Queue();
  // Name: ~Queue() - Destructor
  // Desc: Used to destruct a Queue
  // Preconditions: There is a Queue
  // Postconditions: Queue is deallocated (including dynamically allocated nodes)
  //                 Can just call Clear()
 ~Queue();
  // Name: Queue (Copy Constructor)
  // Preconditions: Creates a copy of existing Queue in separate memory
  //                address (deep copy)
  //                Requires one already existing Queue
  // Postconditions: Copy of existing Queue
  Queue(const Queue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: When two Queue objects exist, sets one to equal another
  //                Requires two Queue objects
  // Postconditions: When completed, you have two Queues in
  //                 separate memory addresses with the same
  //                 number of nodes with the same values in each node
  Queue<T>& operator= (Queue&);
  // Name: PushBack
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Queue
  // Postconditions: Adds a new node to the end of the Queue.
  void PushBack(const T&);
  // Name: PopFront
  // Preconditions: Queue with at least one node. 
  // Postconditions: Removes first node in the queue and
  //                 returns the data in the first node
  T PopFront();
  // Name: Display
  // Preconditions: Outputs the queue.
  // Postconditions: Displays the data in each node of queue
  // Required (used only for queue testing)
  void Display();
  // Name: Front
  // Preconditions: Requires a Queue with at least one node
  // Postconditions: Returns whatever data is pointed at by m_head -
  //                 Does NOT remove node
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a queue
  // Postconditions: Returns if the queue is empty.
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a queue
  // Postconditions: Returns m_size
  int GetSize();
  // Name: Find()
  // Preconditions: Requires a queue
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  int Find(T);
  // Name: Clear
  // Preconditions: Requires a queue
  // Postconditions: Deallocates and removes all nodes in a queue. No memory leaks
  void Clear();
  // Name: At
  // Precondition: Existing Queue
  // Postcondition: Returns object from Queue at a specific location
  // Desc: Iterates to node x and returns data from Queue
  T& At (int x);
  // Name: Swap(int)
  // Preconditions: Requires a queue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  // Example: Swap(1) would swap the node 0 with node 1 so
  //          that node 1 would now be m_head
  // Desc: Swaps two nodes by updating the pointers (not just the value)
  // Hint: Think about the special cases! Implement before Sort
  void Swap(int);
  // Name: Sort()
  // Preconditions: Requires a queue with a minimum of 2 nodes
  //                (otherwise notifies user)
  // Postconditions: Sorts the Queue (may use overloaded < or >).
  // Desc: This is used to sort anything in the Queue assuming the
  //       < or > is overloaded
  //        Uses bubble sort and Swap function above.
  //        Ensure working with queue_test before rest of project.
  // Note: Allowed to use the break command in just this function if necessary
  void Sort();
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};

//**********All Functions Are Required Even If Not Used for Project**************
//**********No references to anything from Movie here*****************


// Constructor
template <class T>
Queue<T>::Queue() {
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

// Destructor
template <class T>
Queue<T>::~Queue() {
    Clear();
}

// Copy constructor
template <class T>
Queue<T>::Queue(const Queue& other) {
    // Initialize member variables
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
    
    // Copy elements from the other queue
    Node<T>* current = other.m_head;
    while (current != nullptr) {
        PushBack(current->GetData());
        current = current->GetNext();
    }
}


// Assignment operator
template <class T>
Queue<T>& Queue<T>::operator=(Queue& other) {
    if (this != &other) {
        // Clear existing data
        Clear();
        
        // Copy elements from the other queue
        Node<T>* current = other.m_head;
        while (current != nullptr) {
            PushBack(current->GetData());
            current = current->GetNext();
        }
    }
    return *this;
}

// Adds a new node to the end of the Queue
template <class T>
void Queue<T>::PushBack(const T& data) {
    // Create a new node with the given data
    Node<T>* newNode = new Node<T>(data);
    if (newNode == nullptr) {
        cerr << "Error: Memory allocation failed for new node." << endl;
        return;
    }

    // Adjust head and tail pointers
    if (m_tail == nullptr) {
        // If the queue is empty, set both head and tail to the new node
        m_head = newNode;
        m_tail = newNode;
    } else {
        // Otherwise, append the new node after the current tail
        m_tail->SetNext(newNode);
        m_tail = newNode;
    }
    m_size++;
}


// Removes the first node in the queue and returns the data in the first node
template <class T>
T Queue<T>::PopFront() {
    if (IsEmpty()) {
        cerr << "Error: Queue is empty. Returning default value." << endl;
        return T();  // Return default-constructed object of type T
    }

    // Retrieve the data from the front node
    T data = m_head->GetData();

    // Move the head pointer to the next node and deallocate memory for the old head
    Node<T>* temp = m_head;
    m_head = m_head->GetNext();
    delete temp;
    m_size--;

    // If the queue is now empty, update the tail pointer as well
    if (m_head == nullptr) {
        m_tail = nullptr;
    }

    return data;
}

// Displays the data in each node of the queue
template <class T>
void Queue<T>::Display() {
    // Start at the head of the queue
    Node<T>* current = m_head;

    // Iterate through each node in the queue
    while (current != nullptr) {
        // Print the data in the current node
        cout << current->GetData();

        // Move to the next node
        current = current->GetNext();

        // If there is another node after this one, print a comma and space
        if (current != nullptr) {
            cout << ", ";
        }
    }

    // Print a newline character at the end to complete the display
    cout << endl;
}


// Returns the data in the first node
template <class T>
T Queue<T>::Front() {
    if (IsEmpty()) {
        cerr << "Error: Queue is empty. Returning default value." << endl;
        return T();  // Return default-constructed object of type T
    }

    // Return the data from the front node
    return m_head->GetData();
}

// Checks if the queue is empty
template <class T>
bool Queue<T>::IsEmpty() {
    return m_size == 0;
}

// Returns the size of the queue
template <class T>
int Queue<T>::GetSize() {
    return m_size;
}


// Finds the index of the given data in the queue
template <class T>
int Queue<T>::Find(T data) {
    Node<T>* current = m_head;
    int index = 0;
    while (current != nullptr) {
        if (current->GetData() == data) {
            return index;
        }
        current = current->GetNext();
        index++;
    }
    // If data is not found, return -1
    return -1;
}

// Deallocates and removes all nodes in the queue
template <class T>
void Queue<T>::Clear() {
    // Loop until the queue is empty
    while (!IsEmpty()) {
        // Remove the first node from the queue
        PopFront();
    }
}



// Returns the data at a specific index
template <class T>
T& Queue<T>::At(int x) {
    // Check if the index is out of bounds
    if (x < 0 || x >= m_size) {
        cerr << "Index out of bounds" << endl;
    }

    // Start at the head of the queue
    Node<T>* current = m_head;

    // Move to the desired index
    for (int i = 0; i < x; i++) {
        current = current->GetNext();
    }

    // Return a reference to the data at the index
    return current->GetData();
}




// Swaps two nodes at the given index
template <class T>
void Queue<T>::Swap(int index) {
    // Check if the index is out of bounds
    if (index < 0 || index > m_size - 1) {
        cerr << "Error: Invalid index for Swap." << endl;
        return;
    }

    // Initialize pointers to the nodes to be swapped
    Node<T>* prev = m_head;
    Node<T>* first = m_head;

    // If the index is 0, no swap is available
    if (index == 0) { 
        cout << "First item. No swap available." << endl;
        return;
    } 
    // If the index is 1, swap the first and second nodes
    else if (index == 1) {
        first = m_head->GetNext();
        Node<T>* second = first->GetNext();
        prev->SetNext(second);
        first->SetNext(prev);
        m_head = first;
    } 
    // For indices greater than 1, find the nodes to swap
    else {
        // Move prev and first pointers to the nodes before the ones to be swapped
        for (int i = 0; i < index - 1; i++) {
            prev = first;
            first = first->GetNext();
        }
        // Get the second node and its next node
        Node<T>* second = first->GetNext();
        if (!second) return; // Safeguard if there is no second node
        Node<T>* nextOfSecond = second->GetNext();
        
        // Perform the swap by updating the next pointers
        prev->SetNext(second);
        second->SetNext(first);
        first->SetNext(nextOfSecond);

        // Update the tail pointer if the swapped pair includes the last node
        if (nextOfSecond == nullptr) {
            m_tail = first;
        }
    }
}



// Sorts the Queue using bubble sort (0-based indexing)
template <class T>
void Queue<T>::Sort() {
    // Check if the queue has less than 2 nodes
    if (m_size < 2) {
        cout << "Queue has less than 2 nodes, cannot be sorted" << endl;
        return;
    }

    // Use bubble sort algorithm to sort the queue
    for (int i = 0; i < m_size - 1; i++) {
        for (int j = 0; j < m_size - i - 1; j++) {
            // Compare adjacent nodes and swap if necessary
            if (At(j) > At(j + 1)) {
                Swap(j + 1);
            }
        }
    }

    // Display the sorted list
    // Note: The Display function is not used here to avoid printing memory addresses of movie objects
    // Uncomment the following lines if you want to test the sorted list with queue_test.cpp
    /*
    cout << "Sorted list: ";
    Display();
    */
}



#endif
