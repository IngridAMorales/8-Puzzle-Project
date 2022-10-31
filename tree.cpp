#include "tree.h"
#include <iostream>
#include <queue>
#include <utility> 
#include <algorithm>
#include <iterator>
#include <vector>
#include <array>

using std::cout; 
using std::endl; 
 

TreeNode* NewNode(std::array<std::array<int,3>,3>& initial, int level){
    TreeNode* newNode = new TreeNode(); 
    int rows = sizeof(newNode->puzzle)/ sizeof(newNode->puzzle[0]);
    int cols = sizeof(newNode->puzzle[0])/ sizeof(newNode->puzzle[0][0]);
     for(int i = 0; i < rows; i++){
        for(int j = 0; j<cols; j++){
            newNode->puzzle[i][j] = initial[i][j];     
        }
    }
    newNode->cost = 0; 
    newNode->depth = level; 
    return newNode; 
}
//passing in the root and the data of the child
void addChild(TreeNode* node, std::array<std::array<int,3>,3>& initial){
    
    TreeNode* newNode = NewNode(initial, node->depth+1); 
    node->children.push_back(newNode); 
    

}
void display(TreeNode* node){
    int rows = sizeof(node->puzzle)/ sizeof(node->puzzle[0]);
    int cols = sizeof(node->puzzle[0])/ sizeof(node->puzzle[0][0]);

    for(int i = 0; i < rows; i++){
        for(int j = 0; j<cols; j++){
           printf("%d ", node->puzzle[i][j]);
           
        }
        printf("\n");
    }
   //cout<<"h(n) = "<< root->cost<<endl; 
     
    /*
    for(int i = 0; i < root->children.size(); i++){
        for(int k = 0; k < rows; k++){
            for(int j = 0; j<cols; j++){
                printf("%d ", root->children[i]->puzzle[k][j]);
            }
        printf("\n");
        }
    }
    */
    
}
int misplacedTiles(std::array<std::array<int,3>,3>& initial, std::array<std::array<int,3>,3>& final){
    int size = initial.size();  
    int counter = 0; 
    for (int i = 0; i <size; i++ ){
        for(int j = 0 ; j<size;j++){
            if(initial[i][j] && initial[i][j] !=final[i][j]){
                counter++;
            }
        }
    }
    return counter; 
}
int manhattanDistance(std::array<std::array<int,3>,3>& initial, std::array<std::array<int,3>,3>& final){
    int size = initial.size();  
    int sum = 0; 
    //find number of misplaces tiles 
    for (int i = 0; i <size; i++ ){
        for(int j = 0 ; j<size;j++){
            if(initial[i][j] && initial[i][j] !=final[i][j]){
                
                //find correct location
                for(int k = 0; k< size ; k++){
                    for(int l = 0; l<size; l++){
                        if(final[k][l]&& final[k][l] == initial[i][j]){
                            sum += abs(k-i)+abs(l-j); 
                        }
                    }
                }

                
            }
            
        }
    }
    
    return sum; 
}

void operators(TreeNode* root){
   
    int rows = sizeof(root->puzzle)/ sizeof(root->puzzle[0]);
    int cols = sizeof(root->puzzle[0])/ sizeof(root->puzzle[0][0]);


    std::array<std::array<int,3>,3> moveLeft; 
    std::array<std::array<int,3>,3> moveRight; 
    std::array<std::array<int,3>,3> moveUp; 
    std::array<std::array<int,3>,3> moveDown; 
    
    std::copy(&root->puzzle[0][0], &root->puzzle[0][0]+rows*cols, &moveRight[0][0]); 
    std::copy(&root->puzzle[0][0], &root->puzzle[0][0]+rows*cols, &moveLeft[0][0]); 
    std::copy(&root->puzzle[0][0], &root->puzzle[0][0]+rows*cols, &moveUp[0][0]); 
    std::copy(&root->puzzle[0][0], &root->puzzle[0][0]+rows*cols, &moveDown[0][0]); 
    
    for(int i = 0; i < rows; i++){
        for(int j = 0; j< cols; j++){
            
            //edge case when (i,j)= (3,3)
           if(root->puzzle[i][j]==0 && j==(cols-1)&& i==(rows-1)){
            
            std::swap(moveLeft[i][j], moveLeft[i][j-1]);
            addChild(root, moveLeft); 
           
            std::swap(moveUp[i][j], moveUp[i-1][j]);
            addChild(root, moveUp); 
            //return root->children; 
           }
           //edge case when (i,j) = (0,0)
           else if(root->puzzle[i][j]==0 && i==0){
            std::swap(moveRight[i][j], moveRight[i][j+1]);
            addChild(root, moveRight); 
           
            std::swap(moveDown[i][j], moveDown[i+1][j]);
            addChild(root, moveDown);
            //return root->children;
           }
           //case when (0,3)
           else if(root->puzzle[i][j]==0 && j==(cols-1) && i==0){
            std::swap(moveLeft[i][j], moveLeft[i][j-1]);
            addChild(root, moveLeft); 

            std::swap(moveDown[i][j], moveDown[i+1][j]);
            addChild(root, moveDown);
            
           }
           //case when (3,0)
           else if(root->puzzle[i][j]==0 && j==0 && i==(rows-1)){
            std::swap(moveRight[i][j], moveRight[i][j+1]);
            addChild(root, moveRight); 


            std::swap(moveUp[i][j], moveUp[i-1][j]);
            addChild(root, moveUp); 
            
           }
           //case when (3,1 or 2)
           else if(root->puzzle[i][j]==0 && i==(rows-1)){
            std::swap(moveRight[i][j], moveRight[i][j+1]);
            addChild(root, moveRight); 

            std::swap(moveLeft[i][j], moveLeft[i][j-1]);
            addChild(root, moveLeft);

            std::swap(moveUp[i][j], moveUp[i-1][j]);
            addChild(root, moveUp); 
            //return root->children;

           }
           //case when (0, 1 or 2)
           else if(root->puzzle[i][j]==0 && i==0){
            std::swap(moveRight[i][j], moveRight[i][j+1]);
            addChild(root, moveRight); 

            std::swap(moveLeft[i][j], moveLeft[i][j-1]);
            addChild(root, moveLeft);

            std::swap(moveDown[i][j], moveDown[i+1][j]);
            addChild(root, moveDown);
            //return root->children;
           }
           //case when (1 or 2 , 0)
           else if(root->puzzle[i][j]==0 && j==0 ){
            std::swap(moveUp[i][j], moveUp[i-1][j]);
            addChild(root, moveUp); 

            std::swap(moveDown[i][j], moveDown[i+1][j]);
            addChild(root, moveDown);

            std::swap(moveRight[i][j], moveRight[i][j+1]);
            addChild(root, moveRight); 
            //return root->children;            
           }
           //case when (1 or 2, 3)
           else if(root->puzzle[i][j]==0 && j==(cols-1)){
            std::swap(moveUp[i][j], moveUp[i-1][j]);
            addChild(root, moveUp); 

            std::swap(moveDown[i][j], moveDown[i+1][j]);
            addChild(root, moveDown);

            std::swap(moveLeft[i][j], moveLeft[i][j-1]);
            addChild(root, moveLeft);   
            //return root->children;         
           }
           //case when (i,j) are in the middle of the puzzle so all operations are allowed
           else if(root->puzzle[i][j]==0 && 0<i<(rows-1)&& 0< j< (cols-1)){
            std::swap(moveUp[i][j], moveUp[i-1][j]);
            addChild(root, moveUp); 

            std::swap(moveDown[i][j], moveDown[i+1][j]);
            addChild(root, moveDown);

            std::swap(moveLeft[i][j], moveLeft[i][j-1]);
            addChild(root, moveLeft);  

            std::swap(moveRight[i][j], moveRight[i][j+1]);
            addChild(root, moveRight);     
            //return root->children;
           }
        }
    
    }
  
    
}


TreeNode* search(std::array<std::array<int,3>,3>& initial, std::array<std::array<int,3>,3>& final){

    //creating queue
    std::priority_queue<TreeNode*,std::vector<TreeNode*>,comp> q;  
    //making node 
    TreeNode* root = NewNode(initial, 0); 
    root->cost = manhattanDistance(initial, final); 

    //pushing node 
    q.push(root);
    cout<<"root:"<<endl; 
    display(q.top()); 
    
    
    while(!q.empty()){
        TreeNode* min = q.top(); 

        if(q.empty()){
            return nullptr; 
        }  
        q.pop(); 
        //Check for goal state
        if(min->puzzle == final){
            cout<<"we have entered goal state"<<endl; 
            cout<<"Found at depth "<<min->depth<< " with total cost of "<< min->cost +min->depth<<endl; 
            return min; 
        }
        else{       
            
            cout<<"we are creating children of"<<endl;
            display(min); 
            cout<<"with depth "<< min->depth<<endl; 
            operators(min); 
            
            for(int i = 0; i < min->children.size(); i++){
                
                cout<<"Child "<<i<<endl;
                
                min->children.at(i)->cost = manhattanDistance(min->children.at(i)->puzzle, final); 
               
                display(min->children.at(i)); 
                cout<<"f(n) = "<< min->children.at(i)->cost +min->children.at(i)->depth<<endl;
                q.push(min->children.at(i)); 
                
            } 

        }
        //q.pop(); 
       
                   
    }
    return q.top(); 
} 





