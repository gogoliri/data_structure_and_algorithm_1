#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * @brief creates a vector of integers with ascending numbers from 0 - n-1
 *
 * @param n the size of the vector to be created
 * @return std::vector<int>
 */
std::vector<int> ascendingVector(int n){
    // std::vector<int> v;
    // for ( int i = 0; i < n ; i++){
    //     v.insert(v.end(), i);
    // }
    // return v;

    vector<int> v(n);
    std::iota (std::begin(v), std::end(v), 0);
    return v;
}
