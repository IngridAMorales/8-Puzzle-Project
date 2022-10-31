
#ifndef __TREE_H__
#define __TREE_H__

#include <vector>
#include <queue>
#include <array>

struct TreeNode* NewNode(std::array<std::array<int,3>,3>& initial, int level); 
void addChild(TreeNode* node, std::array<std::array<int,3>,3>& initial); 
void display(TreeNode* root); 
struct TreeNode* search(std::array<std::array<int,3>,3>& initial, std::array<std::array<int,3>,3>& final); 
void operators(TreeNode* node); 
int misplacedTiles(std::array<std::array<int,3>,3>& initial, std::array<std::array<int,3>,3>& final);
int manhattanDistance(std::array<std::array<int,3>,3>& initial, std::array<std::array<int,3>,3>& final); 



struct TreeNode{ 

    TreeNode* parent; 
    std::array<std::array<int,3>,3> puzzle;
    std::vector <TreeNode*> children; 
    int depth; 
    int cost; 

};
struct comp
{
    bool operator()(const TreeNode* lhs, const TreeNode* rhs) const
    {
        return (lhs->cost + lhs->depth) > (rhs->cost + rhs->depth);
    }
};


#endif 