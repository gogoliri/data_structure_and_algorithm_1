#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


/**
 * @brief duplicates even numbers in the vector, removes uneven numbers. Example: {1, 2, 3 4} -> {2, 2, 4, 4}
 *
 * @param vec vector to be handled
 */
void duplicateEvenRemoveUneven(std::vector<int>& vec) {

    using Iter = std::vector<int>::iterator;

    const unsigned long s = vec.size();
    vec.reserve(2*s);
    Iter begin = vec.begin();
    Iter end = vec.end();
    unsigned long a = 0;
    for ( Iter it = begin; it < end+s; it++){
        a++;
        if ( *it % 2 == 0 ){
            it =vec.insert(it, *it );
            it++;
        }
        else {
            it = vec.erase(it);
            it--; 
        }
        if(a>=s){break;}
    }
}

