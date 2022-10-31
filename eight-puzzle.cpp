#include <iostream>
#include <vector> 
#include <utility> 
#include <array>
#include "tree.h"
using namespace std; 



int main(){

    
    std::array<std::array<int,3>, 3> initial = {{{4,1,2}, {5,3,0},{7,8,6}}};

    std::array<std::array<int,3>,3> final = {{{1,2,3}, {4,5,6}, {7,8,0}}}; 
    
    TreeNode* node; 
    node = search(initial, final); 
   
    display(node); 
   return 0; 
}







 
