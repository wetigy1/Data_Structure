#include "list.h"

//测试case


int main()
{
    ListNode List;
    Item item,deleteitem;

    /*===============测试case: 初始化链表==============*/
    InitList(&List);

    /*===============测试case: 添加节点==============*/
    for(int i = 0; i < 10; i++){
        item.Value = i;
        AddListNode(item,&List);
    }

    /*===============测试case: 输出节点==============*/
    ShowListNode(&List);

    /*===============测试case: 统计节点个数==============*/
    cout <<" ListNodeCnt :" <<ListNodeCnt(&List) << endl;

    /*===============测试case: 删除指定节点并输出==============*/
    deleteitem.Value = 9;
    DeleteListNode(deleteitem,&List);
    ShowListNode(&List);

    /*===============测试case: 删除节点并输出==============*/
    ClearList(&List);

    return 0;

}
