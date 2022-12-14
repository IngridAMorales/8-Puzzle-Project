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
    int size = initial.size(); 
     for(int i = 0; i < size; i++){
        for(int j = 0; j<size; j++){
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
        cout<< "["; 
        for(int j = 0; j<cols; j++){
           printf(" %d ", node->puzzle[i][j]);
        }
        cout<< "]"<<endl; 
    }
    printf("\n");
    
}
int misplacedTiles(std::array<std::array<int,3>,3>& initial, std::array<std::array<int,3>,3>& final){
    int size = initial.size();  
    int counter = 0; 

    //finds the number of misplaced tiles 
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
    //find number of misplaced tiles 
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

    //initializing the arrays that hold the states of the children
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
            
            //edge case when (i,j)= (2,2) is the location of the blank space 
           if(root->puzzle[i][j]==0 && j==(cols-1)&& i==(rows-1)){
   
            std::swap(moveLeft[i][j], moveLeft[i][j-1]);
            addChild(root, moveLeft); 
           
            std::swap(moveUp[i][j], moveUp[i-1][j]);
            addChild(root, moveUp); 
           
           }
           //edge case when (i,j) = (0,0) is the location of the blank space 
           else if(root->puzzle[i][j]==0 && i==0 && j==0){
  
            std::swap(moveRight[i][j], moveRight[i][j+1]);
            addChild(root, moveRight); 
           
            std::swap(moveDown[i][j], moveDown[i+1][j]);
            addChild(root, moveDown);

           }
           //case when (0,2) is the location of the blank space 
           else if(root->puzzle[i][j]==0 && j==(cols-1) && i==0){
          
            std::swap(moveLeft[i][j], moveLeft[i][j-1]);
            addChild(root, moveLeft); 

            std::swap(moveDown[i][j], moveDown[i+1][j]);
            addChild(root, moveDown);
            
           }
           //case when (2,0) is the location of the blank space 
           else if(root->puzzle[i][j]==0 && j==0 && i==(rows-1)){
            std::swap(moveRight[i][j], moveRight[i][j+1]);
            addChild(root, moveRight); 


            std::swap(moveUp[i][j], moveUp[i-1][j]);
            addChild(root, moveUp); 
            
           }
           //case when (2,1) is the location of the blank space 
           else if(root->puzzle[i][j]==0 && i==(rows-1)){
            std::swap(moveRight[i][j], moveRight[i][j+1]);
            addChild(root, moveRight); 

            std::swap(moveLeft[i][j], moveLeft[i][j-1]);
            addChild(root, moveLeft);

            std::swap(moveUp[i][j], moveUp[i-1][j]);
            addChild(root, moveUp); 
        

           }
           //case when (0, 1) is the location of the blank
           else if(root->puzzle[i][j]==0 && i==0){
            std::swap(moveRight[i][j], moveRight[i][j+1]);
            addChild(root, moveRight); 

            std::swap(moveLeft[i][j], moveLeft[i][j-1]);
            addChild(root, moveLeft);

            std::swap(moveDown[i][j], moveDown[i+1][j]);
            addChild(root, moveDown);
    
           }
           //case when (1, 0) is the location of the blank 
           else if(root->puzzle[i][j]==0 && j==0 ){
            std::swap(moveUp[i][j], moveUp[i-1][j]);
            addChild(root, moveUp); 

            std::swap(moveDown[i][j], moveDown[i+1][j]);
            addChild(root, moveDown);

            std::swap(moveRight[i][j], moveRight[i][j+1]);
            addChild(root, moveRight); 
                       
           }
           //case when (1, 2) is the location of the blank space
           else if(root->puzzle[i][j]==0 && j==(cols-1)){
            std::swap(moveUp[i][j], moveUp[i-1][j]);
            addChild(root, moveUp); 

            std::swap(moveDown[i][j], moveDown[i+1][j]);
            addChild(root, moveDown);

            std::swap(moveLeft[i][j], moveLeft[i][j-1]);
            addChild(root, moveLeft);   
                    
           }
           //case when (i,j) are in the middle of the puzzle so all operations are allowed
           else if(root->puzzle[i][j]==0 && 0<i<(rows-1)&& 0< j< (cols-1)){
            std::swap(moveUp[i][j], moveUp[i-1][j]);
            addChild(root, moveUp); 

            std::swap(moveDown[i][j], moveDown[i+1][j]);
            addChild(root, moveDown);

            std::swap(moveRight[i][j], moveRight[i][j+1]);
            addChild(root, moveRight); 

            std::swap(moveLeft[i][j], moveLeft[i][j-1]);
            addChild(root, moveLeft);  
           }
        }
    
    }
  
    
}


TreeNode* search(std::array<std::array<int,3>,3>& initial, std::array<std::array<int,3>,3>& final, int queueFunction){

    //creating queue
    std::priority_queue<TreeNode*,std::vector<TreeNode*>,comp> q;  

    //making root node 
    TreeNode* root = NewNode(initial, 0); 

    //chooses the heuristic based on user input
    if( queueFunction == 1){
        root->cost = 0; 
    }
    else if(queueFunction ==2){
        root->cost = misplacedTiles(initial, final); 
    }
    else {
        root->cost = manhattanDistance(initial, final); 
    }
    
    //pushing node 
    q.push(root);
   
    int max = q.size();  
    int nodes = 1; 
 
    while(!q.empty()){

        //saving the top node in queue before popping 
        TreeNode* firstNode = q.top(); 

        //in case there is no solution 
        if(q.empty()){
            return nullptr; 
        } 

        q.pop(); 

        //Check for goal state
        if(firstNode->puzzle == final){
            cout<<"Solution depth was "<<firstNode->depth<<endl; 
            cout<<"Max queue size is "<< max<<endl; 
            cout<<"Nodes expanded is "<< nodes<<endl;

            return firstNode; 
        }
        else{       
            //creating children of the node popped 
            operators(firstNode); 

            //pushing the children created into queue
            for(int i = 0; i < firstNode->children.size(); i++){

                //chooses the heuristic based on user input
                if( queueFunction == 1){
                    firstNode->cost = 0; 
                }
                else if(queueFunction ==2){
                    firstNode->children.at(i)->cost = misplacedTiles(firstNode->children.at(i)->puzzle, final); 
                }
                else {
                    firstNode->children.at(i)->cost = manhattanDistance(firstNode->children.at(i)->puzzle, final); 
                }
                //pushing children into queue
                q.push(firstNode->children.at(i));   

                //keeping count of the number of nodes expanded each time we create a child
                nodes++; 
            } 

            //getting the max queue size 
            if (q.size()> max){
                max = q.size(); 
            }
        } 
        cout<<"The best state to expand with a g(n) = "<<q.top()->depth<< " and h(n) = "<< q.top()->cost << " is... "<< endl;
        display(q.top());
        
    } 
    return q.top(); 
} 





