#include <iostream>
#include <string>
using namespace std;
#include "Queue.cpp"

// To test just queue follow these instructions:
//   1.  Comment out any tests below that you haven't written the functions for.
//   2.  make qtest (calls g++ -Wall Queue.cpp queue_test.cpp -o qtest)
//   3.  make qtest2 (calls valgrind ./qtest)


//*********Testing Constants***************
const int test1 = 10;
const int test2 = 20;
const int test3 = 30;
const int test4 = 40;

int main () {

  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor, PushBack, and Display" << endl;
  //Test Default Constructor
  Queue <int> *newQ1 = new Queue <int>(); //Default constructor
  //Push 3 nodes into Queue
  newQ1->PushBack(test1); //PushBack
  newQ1->PushBack(test2); //PushBack
  newQ1->PushBack(test3); //PushBack
  cout << "Should output 10, 20, 30 using Display (one on each line)" << endl;
  newQ1->Display();
  cout << "End Test 1 - Constructor, PushBack, and Display" << endl << endl;

  //Test 2 - Copy Constructor Test
  cout << "Test 2 - Copy Constructor Running" << endl;
  //Test Copy constructor
  Queue <int> *newQ2 = new Queue <int>(*newQ1); //Copy Constructor
  cout << "Should output 10, 20, 30 using Display (one on each line)" << endl;
  newQ2->Display(); //Testing copy made
  cout << "Size below should match. Location should not" << endl;
  cout << "Source size: " << newQ1->GetSize() << " and Copied size: "
       << newQ2->GetSize() << endl;
  cout << "Source location: " << &newQ1 << " and Copied location: "
       << &newQ2 << endl; //Display memory addresses
  cout << "End Test 2 - Copy" << endl << endl;
  
  //Test 3 - Overloaded Assignment Operator Test
  cout << "Test 3 - Overloaded Assignment Operator Test and At()" << endl;
  //Create new Queue using constructor
  Queue <int> *newQ3 = new Queue <int>(); //Constructs new Queue
  //Update using overloaded assignment operator
  *newQ3 = *newQ1; //Calls overloaded assignment operator
  cout << "Should output 10,20,30" << endl;
  cout << newQ3->At(0) << ',' << newQ3->At(1)  << ',' << newQ3->At(2) << endl;
  cout << "size below should match. Location should not" << endl;
  cout << "Source size: " << newQ1->GetSize() << " and Assigned size: "
       << newQ3->GetSize() << endl;
  cout << "Source location: " << &newQ1 << " and Assigned location: "
       << &newQ3 << endl; //Displays memory addresses
  cout << "End Test 3 - Assignment" << endl << endl;
  
  //Test 4 - Test Pop
  cout << "Test 4 - PopFront" << endl;
  cout << "Size before: " << newQ1->GetSize() << " ";
  cout << "Removed: " << newQ1->PopFront() << endl;
  cout << "Size after: " << newQ1->GetSize() << endl;
  cout << "End Test 4 - PopFront" << endl << endl;
  
  //Test 5 - Test GetSize and Clear
  cout << "Test 5 - GetSize and Clear Running" << endl;
  //Test size()
  cout << "Outputting GetSize" << endl;
  cout << newQ2->GetSize() << endl;
  //Test Clear()
  cout << "Clearing all nodes" << endl;
  newQ2->Clear();
  cout << "Outputting the size (should now be 0)" << endl;
  cout << newQ2->GetSize() << endl << endl;

  //Test 6 - Test Find
  cout << "Test 6 - Find" << endl;
  cout << "Try to find 10 (Should NOT find it)" << endl;
  if(newQ1->Find(test1) != -1){
    cout << "10 Found" << endl;
  }else{
    cout << "10 NOT Found" << endl;
  }
  cout << "Try to find 20 (Should find it)" << endl;
  if(newQ1->Find(test2) != -1){
    cout << "20 Found" << endl << endl;
  }else{
    cout << "20 NOT Found" << endl << endl;
  }

  //Test 7 - Test Swap
  cout << "Test 7 - Test Swap" << endl;
  Queue <int> *newQ4 = new Queue <int>();
  //Push 4 nodes into Queue
  newQ4->PushBack(test1);
  newQ4->PushBack(test2);
  newQ4->PushBack(test3);
  newQ4->PushBack(test4);
  cout << "7A - Swap(1)" << endl;
  newQ4->Swap(1);
  cout << "Should output 20, 10, 30, 40" << endl;
  cout << newQ4->At(0) << ',' << newQ4->At(1)  << ',' << newQ4->At(2) << ','
       << newQ4->At(3) << endl;

  cout << "7B - Swap(3)" << endl;
  newQ4->Swap(3);
  cout << "Should output 20, 10, 40, 30" << endl;
  cout << newQ4->At(0) << ',' << newQ4->At(1)  << ',' << newQ4->At(2) << ','
       << newQ4->At(3) << endl;

  cout << "7C - Swap(2)" << endl;
  newQ4->Swap(2);
  cout << "Should output 20, 40, 10, 30" << endl;
  cout << newQ4->At(0) << ',' << newQ4->At(1)  << ',' << newQ4->At(2) << ','
       << newQ4->At(3) << endl;

  cout << "7D - PushBack(50)" << endl;
  newQ4->PushBack(50);  //Checking to make sure that m_tail is correct after swap
  cout << "Should output 20, 40, 10, 30, 50" << endl;
  cout << newQ4->At(0) << ',' << newQ4->At(1)  << ',' << newQ4->At(2) << ',' << newQ4->At(3) << ',' << newQ4->At(4) << endl;
  cout << "End Test 7 - Swap" << endl << endl;
  
  //Test 8 - Test Destructor
  cout << "Test 8 - Sort" << endl;
  newQ4->Sort();
  cout << "Should output 10, 20, 30, 40, 50" << endl;
  cout << "End Test 8 - Sort" << endl << endl;
  
  //Test 9 - Test Destructor
  cout << "Test 9 - Test Destructor" << endl;
  cout << "delete newQ1" << endl;
  delete newQ1;
  cout << "delete newQ2" << endl;
  delete newQ2;
  cout << "delete newQ3" << endl;
  delete newQ3;
  cout << "delete newQ4" << endl;
  delete newQ4;
  cout << "End Test 9 - Destructors" << endl;
  return 0;
}

