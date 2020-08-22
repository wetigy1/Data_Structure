#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

typedef struct data{
    int Value;
}Item;

typedef struct node{
    Item m_Value;
    node* m_pNext;
}Node;

typedef Node* ListNode;

void InitList(ListNode *pList);
unsigned int ListNodeCnt(const ListNode *pList);
void AddListNode(Item item, ListNode *pList);
void DeleteListNode(Item item, ListNode *pList);
void ShowListNode(const ListNode *pList);
void ClearList(ListNode *pList);

#endif // LIST_H
