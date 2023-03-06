#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh" // NOT_FOUND constant

using namespace std;


/**
 * @brief Find the median value of a given vector, whose elements are in random
 *        order. Return NOT_FOUND if the size of the vector is zero.
 *
 * @param v a random vector
 * @return int
 */


int findMedian(std::vector<int>& v)
{   
    if(v.size()==0){
        return NOT_FOUND;
    }else if(v.size()%2==1){
        auto n = v.size() / 2;      
        nth_element(v.begin(), v.begin()+n, v.end());
        return v[n];
    }else{
        auto n = v.size()/2 -1;
        nth_element(v.begin(), v.begin()+n, v.end());
        nth_element(v.begin(), v.begin()+n+1, v.end());
        return (v[n]+v[n+1])/2;

    }


}

