#ifndef TREE_H
#define TREE_H

#include <iostream>

#define MAXITMES 20

using namespace std;

typedef struct data{
    int Value;
}Item;

typedef struct tree_node{
    Item item;          //节点数据内容
    tree_node* m_left;  //指向左分支的指针
    tree_node* m_right; //指向右分支的指针
}Tree_Node;

typedef struct tree{
    Tree_Node *root;   //指向根节点的指针
    int size;          //树的大小
}Tree;


void InitTree(Tree *ptree);
bool TreeIsEmpty(const Tree *ptree);
bool TreeIsFull(const Tree *ptree);
int TreeNodeCnt(const Tree *ptree);
bool AddItem(const Item *item, Tree *ptree);
bool DeleteItem(const Item * item, Tree * ptree);
void ClearTree(Tree *ptree);


//前序遍历
void PreorderTraversal(const Tree_Node *ptree_node);
//中序遍历
void InorderTraversal(const Tree_Node *ptree_node);
//后序遍历
void PostorderTraversal(const Tree_Node *ptree_node);

#endif // TREE_H
