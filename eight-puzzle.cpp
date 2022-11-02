#include <iostream>
#include <vector> 
#include <utility> 
#include <array>
#include <chrono>
#include "tree.h"
using namespace std; 
using namespace std::chrono;


int main(){
    
    int input;
    std::array<std::array<int,3>,3> final = {{{1,2,3}, {4,5,6}, {7,8,0}}}; 
  
    cout<<endl << "Welcome to my 8 puzzle Solver. Type '1' to use a default puzzle, or '2' to create your own. "<<endl;
    do{ 
    cin>>input; 
   
    if(input ==1 ){
        std::array<std::array<int,3>, 3> initial = {{{2,1,3}, {4,7,6},{5,8,0}}};


        do{
        cout<<"Select algorithm: "<<endl; 
        cout<<"(1) for Uniform Cost Search, "<<endl;
        cout<<"(2) for the Misplaced Tile, "<<endl; 
        cout<<"(3) the Manhattan Distance Heuristic. "<<endl;
        cin>>input; 

        if(input == 1){
            TreeNode* node; 
            node = search(initial, final, 1); 
            cout<<endl<<"Goal state! "<<endl;
            display(node); 
            break; 
            
        }
        else if(input== 2){
            TreeNode* node; 
            node = search(initial, final, 2); 
            cout<<endl<<"Goal state! "<<endl;
            display(node); 
            break; 
            
        }
        else if( input == 3){
            TreeNode* node; 
            node = search(initial, final, 3); 
            cout<<endl<<"Goal state! "<<endl;
            display(node);
            break; 
            
        }
        else{
            cout<<"Enter '1', '2', or '3' "<<endl; 
            
        }
        }while(input != 1 || input!= 2 ||input != 3); 
        break;
        
    }
    else if( input == 2){
        std::array<std::array<int,3>, 3> initial; 

        cout<< "Enter your puzzle, using a zero to represent the blank. Please only enter valid 8-puzzles. \nEnter the puzzle by row and the numbers with a space. \nType RETURN only when finished. "<<endl; 
        cout<<"Enter the first row: "<<endl; 
        cin>>initial[0][0]>>initial[0][1]>>initial[0][2];
        cin.ignore(); 
        cout<<"Enter the second row: "<<endl; 
        cin>>initial[1][0]>>initial[1][1]>>initial[1][2]; 
        cin.ignore(); 
        cout<<"Enter third row: "<<endl; 
        cin>>initial[2][0]>>initial[2][1]>>initial[2][2]; 
        cin.ignore(); 
        do{
        cout<<"Select algorithm: "<<endl; 
        cout<<"(1) for Uniform Cost Search, "<<endl;
        cout<<"(2) for the Misplaced Tile, "<<endl; 
        cout<<"(3) the Manhattan Distance Heuristic. "<<endl;
        cin>>input; 
         
         if(input == 1){
            TreeNode* node; 
            node = search(initial, final, 1); 
            cout<<endl<<"Goal state! "<<endl;
            display(node); 
            break;
        }
        else if(input== 2){
            TreeNode* node; 
            node = search(initial, final, 2); 
            cout<<endl<<"Goal state! "<<endl;
            display(node); 
            break;
        }
        else if( input == 3){
            TreeNode* node; 
            node = search(initial, final, 3); 
            cout<<endl<<"Goal state! "<<endl;
            display(node); 
            break;
        }
        else{
            cout<<"Enter '1', '2', or '3' "<<endl; 
            
        }
        } while(input!= 1 ||input != 2 ||input!= 3);
        break; 
    }
    else{
        cout<<"please input '1' or '2'"<<endl; 
    }
    }while(input!= 1 || input!= 2);
    
   return 0; 
}







 
