/**
 * iteration3.cc
 *
 * Print beginning half of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include <iostream>
#include <iterator> // for iterators
#include <list> // for lists
using namespace std;


void printHalf(const list<int>& lst)
{
  /**
  * Use iterators to go through the list and print elements
  */

  // ADD YOUR CODE HERE
  unsigned long s = lst.size()/2 ;
  unsigned long a = 0;
  for(auto it= lst.begin(); it != lst.end(); ++it){
    if(a < s){
      cout<< *it << " ";
    }
    a++;
  }
  cout<<endl;


}
