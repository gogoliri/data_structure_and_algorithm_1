#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;


/**
 * @brief Erases every second item from the vector. Example: {1, 2, 3, 4} -> {1, 3}
 *
 * @param vec vector where every second item is erased.
 */
void eraseEverySecond(std::vector<int>& vec) {
    auto beg = vec.begin();
    auto end = vec.end();
    unsigned long s = vec.size()/2 ;
    unsigned long a = 0;
    for (auto  i = beg+1; i != end ; i = i+1)
    {  
        vec.erase(i);
        a++;
        if(a>= s){
            break;
        }

        
        
    }
}

