#include "tree.h"


int main()
{
    Tree tree;

    cout <<"/*===============Test_case: InitTree==============*/"<< endl;
    InitTree(&tree);

    cout <<"/*===============Test_case: tree_status==============*/"<< endl;
    bool tree_status = false;

    tree_status = TreeIsEmpty(&tree);
    cout << "TreeIsEmpty Status :" << tree_status << endl;

    tree_status = TreeIsFull(&tree);
    cout << "TreeIsFull Status :" << tree_status << endl;

    cout <<"/*===============Test_case: TreeNodeCnt==============*/"<< endl;
    int node_cnt = 0;
    node_cnt = TreeNodeCnt(&tree);
    cout << "TreeNodeCnt : " << node_cnt << endl;

    cout <<"/*===============Test_case: AddItem==============*/"<< endl;
    Item item;
    for(int i = 0; i < 10; i++){
        item.Value = 10 - i;
        AddItem(&item,&tree);
    }
    for(int i = 0; i < 10; i++){
        item.Value = 20 - i;
        AddItem(&item,&tree);
    }
    cout << "TreeIsEmpty Status :" << TreeIsEmpty(&tree) << endl;
    cout << "TreeIsFull Status :" << TreeIsFull(&tree) << endl;
    cout << "TreeNodeCnt : " << TreeNodeCnt(&tree) << endl;

    cout <<"/*===============Test_case: Traversal==============*/"<< endl;
    Tree traversaltree;
    InitTree(&traversaltree);
    int value_arry[8] = {4,2,6,3,5,1,7,9};
    for(int i = 0; i < 8; i++){
        item.Value = value_arry[i];
        AddItem(&item,&traversaltree);
    }
    /*二叉树数据图例如下:
                         4
                    /         \
                  2             6
               /     \        /    \
              1       3      5      7
                                     \
                                      9
    */

    PreorderTraversal(traversaltree.root);
    InorderTraversal(traversaltree.root);
    PostorderTraversal(traversaltree.root);

    while(1);
}
