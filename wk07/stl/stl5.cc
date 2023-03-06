#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Arrange vector in three subsequent sections:
 *        - those divisible by three (asc order)
 *        - those whose reminder is 1 (asc order)
 *        - those whose reminder is 2 (asc order)
 * @param v a sortable vector
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
bool mod3sort(int i,int j) {
  if(i%3 == j%3){
    return i<j;
  }
  else{
    return (i%3) < (j%3);
  }
}
int sortMod3(std::vector<int>& v)
{ 
  try{
    sort(v.begin(), v.end(), mod3sort);
    return EXIT_SUCCESS;
  }catch(exception()){
    return EXIT_FAILURE;
  }
}

