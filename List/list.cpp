#include "list.h"

void InitList(ListNode *pList)
{
    *pList = nullptr;
}

unsigned int ListNodeCnt(const ListNode *pList)
{
    unsigned int nodecnt = 0;
    //检查输入的链表是否为空
    ListNode pListNode = *pList;
    if(pListNode == nullptr){
        return 0;
    }
    while (pListNode != nullptr)
    {
        nodecnt++;
        pListNode = pListNode->m_pNext;
    }
    return nodecnt;
}

void AddListNode(Item item, ListNode *pList)
{
    //以指针的形式创建新的链表,在原有的链表数据上添加节点
     ListNode pListNode = *pList;

    //先创建一个新链表保存元素内容
    ListNode pNEW = new Node();
    pNEW->m_Value.Value = item.Value;
    pNEW->m_pNext = nullptr;


    //检查链表是否为空
    if(pListNode ==  nullptr){
        *pList = pNEW;
    }else{
        //循环指向最后一个节点，
        while(pListNode->m_pNext != nullptr){
            pListNode = pListNode->m_pNext;
        }
        //在链表末端插入新元素
        pListNode->m_pNext = pNEW;
    }
}
void DeleteListNode(Item item, ListNode *pList)
{
    //检查是不是空链表
    if(*pList == nullptr){
        return;
    }

    ListNode pDeleteListNode = nullptr;

    //检查删除的节点是不是存在,若存在检查是不是头节点
    if((*pList)->m_Value.Value == item.Value){
        pDeleteListNode = *pList;
        *pList = (*pList)->m_pNext;
    }else {
        //若不是头节点，轮询查找节点
        ListNode pListNode = *pList;
        while ((pListNode->m_pNext != nullptr) &&(pListNode->m_pNext->m_Value.Value != item.Value)){
            pListNode = pListNode->m_pNext;
        }
        if((pListNode->m_pNext != nullptr) && pListNode->m_pNext->m_Value.Value == item.Value){
            pDeleteListNode = pListNode->m_pNext;
            pListNode->m_pNext = pListNode->m_pNext->m_pNext;

        }
    }

    if(pDeleteListNode != nullptr){
        delete pDeleteListNode;
        pDeleteListNode = nullptr;
    }
}

void ShowListNode(const ListNode *pList)
{
    //检查输入的链表是否为空
    ListNode pListNode = *pList;
    if(pListNode == nullptr){
        return;
    }
    while (pListNode != nullptr)
    {
        cout << " m_Value Value :" << pListNode->m_Value.Value << endl;
        pListNode = pListNode->m_pNext;
    }
}

void ClearList(ListNode *pList)
{

    ListNode pNode = nullptr;

    if((*pList) == nullptr){
        return;
    }

    while ((*pList) != nullptr){
        pNode = (*pList)->m_pNext; //保存下一个节点
        delete (*pList);           //删除当前节点
        (*pList) = pNode;          //指向下一个节点
    }

}

