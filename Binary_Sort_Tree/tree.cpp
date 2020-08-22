#include "tree.h"

typedef struct pair{
    Tree_Node * parent;
    Tree_Node * child;
}Pair;

//局部函数：产生新节点
static Tree_Node * MakeNode(const Item * item)
{
    Tree_Node *new_node = nullptr;
    //检查内存分配是否成功,并赋值，使用new不能使用判断内存地址为空的方式来判断内存是否分配成功，应该要使用try catch,但是使用malloc可以用判断内存地址是否为空的方式
    try {
      new_node = new Tree_Node;

    } catch (const bad_alloc& e) {
        cout<<e.what()<<endl;
        cout<<"Allocated memory exception." << endl;
    }

    new_node->item = *item;
    new_node->m_left = nullptr;
    new_node->m_right = nullptr;

    return new_node;
}

//局部函数：判断新节点是否可以放在左子树
static bool ToLeft(const Item * new_item, const Item * tree_item)
{
    if(new_item->Value < tree_item->Value){
        return true;
    }else{
        return false;
    }
}

//局部函数：判断新节点是否可以放在右子树
static bool ToRight(const Item * new_item, const Item * tree_item)
{
    if(new_item->Value > tree_item->Value){
        return true;
    }else{
        return false;
    }
}

//局部函数：添加节点
static bool AddNode(Tree_Node * new_node, Tree_Node * root)
{
    if(ToLeft(&new_node->item,&root->item)){
        if(root->m_left == nullptr){
            root->m_left = new_node;
            return true;
        }else{
           AddNode(new_node,root->m_left);
        }
    }
    else if(ToRight(&new_node->item,&root->item)){
        if(root->m_right == nullptr){
            root->m_right = new_node;
            return true;
        }else{
           AddNode(new_node,root->m_right);
        }
    }
    else{
        return false;
    }

    return true;
}

//局部函数：删除节点
static void DeleteNode(Tree_Node **ptr_node)
{
    /*  要想好的处理方式：
        1.待删除的节点没有字节点，只要把父节点中的指针重置成nullptr,并释放掉已删除节点的内存。
        2.待删除的节点带有一个节点，把已删除节点的父节点指针指向已删除节点的子树地址,有可能是左节点，或者右节点
        3.待删除的节点带有两个节点，(1).把左子树与已删除节点的父节点连接起来，(2).沿着左子树的右节点找到第一个空位把右子树连接上。
    */

    Tree_Node *delete_node = nullptr; //表示待删除的节点
    if((*ptr_node)->m_left == nullptr){
        delete_node = *ptr_node;
        *ptr_node = (*ptr_node)->m_right;
        delete delete_node;
    }else if ((*ptr_node)->m_right == nullptr) {
        delete_node = *ptr_node;
        *ptr_node = (*ptr_node)->m_left;
        delete delete_node;
    }else {
        //for 循环找到左子树的右节点为空的位置
        for (delete_node = (*ptr_node)->m_left; delete_node->m_right != nullptr; delete_node = delete_node->m_right) {
            continue;
        }
        delete_node->m_right = (*ptr_node)->m_right; //左子树的右节点第一个空位连接上右节点
        delete_node = *ptr_node;
        *ptr_node = (*ptr_node)->m_left;

        delete delete_node;
    }
}

//局部函数：清除所有节点
static void ClearALLNode(Tree_Node *ptree_node)
{
    //实现思路
    Tree_Node *p_right_node = nullptr;
    if(ptree_node != nullptr){
        p_right_node = ptree_node->m_right;
        ClearALLNode(ptree_node->m_left);
        delete ptree_node; //一旦删除，右节点的地址会消失，所以先保存右节点的地址
        ClearALLNode(p_right_node);
    }
}

//局部函数：检查节点参数是否已经存在
static Pair CheckItem(const Item * item, Tree * ptree)
{
    Pair look;
    look.parent = nullptr;
    look.child = ptree->root;

    //输出参数检查
    if(look.child == nullptr){
        return look;
    }

    //循环检查节点参数
    while (look.child != nullptr) {
        if(ToLeft(item,&ptree->root->item)){
            look.parent = look.child;
            look.child = look.child->m_left;
        }
        else if(ToRight(item,&ptree->root->item)){
            look.parent = look.child;
            look.child = look.child->m_right;
        }
        else{
            break;
        }
    }

    return look;
}

void InitTree(Tree *ptree)
{
    ptree->root = nullptr;
    ptree->size = 0;
}

bool TreeIsEmpty(const Tree *ptree)
{
    if(ptree->root == nullptr){
        return true;
    }else {
        return false;
    }
}

bool TreeIsFull(const Tree *ptree)
{
    if(ptree->size == MAXITMES){
        return true;
    }else {
        return false;
    }
}

int TreeNodeCnt(const Tree *ptree)
{
    return ptree->size;
}

bool AddItem(const Item *item, Tree *ptree)
{
    //输入参数检查
    if(TreeIsFull(ptree)){
        cout <<"tree is full" << endl;
        return false;
    }

    //检查要添加的数据是否已经存在
    if(CheckItem(item,ptree).child != nullptr){
        cout <<"The node to be created already exists" << endl;
        return false;
    }

    //创建新节点
    Tree_Node *new_mode = MakeNode(item);

    //检查是否创建新节点是否成功
    if(new_mode == nullptr){
        cout << "New node creation failed" << endl;
        return false;
    }

    //添加节点到树中,先检查树是否为空
    if(ptree->root == nullptr){
        ptree->root = new_mode;
        ptree->size++;
    }else {
        if(AddNode(new_mode,ptree->root)){
          ptree->size++;
        }
    }

    return true;

}

bool DeleteItem(const Item * item, Tree * ptree)
{
    Pair look;
    look = CheckItem(item,ptree);
    //检查项是否存在
    if(look.child == nullptr){
        cout <<"The item no exists" << endl;
        return false;
    }
    //检查项的父节点是否存在，若存在则为根节点，直接删除根节点即可
    if(look.parent == nullptr){
        DeleteNode(&ptree->root);
    }else if (look.parent->m_left == look.child) {
         DeleteNode(&look.parent->m_left);
    }else {
         DeleteNode(&look.parent->m_right);
    }

    ptree->size--; //这种删除节点的方式不对

    return true;
}

//清空树
void ClearTree(Tree *ptree)
{
    if(ptree != nullptr){
        ClearALLNode(ptree->root);
    }
    ptree->root = nullptr;
    ptree->size = 0;
}

void PreorderTraversal(const Tree_Node *ptree_node)
{
    if(ptree_node == nullptr){
        return;
    }

    //原则：先访问根节点，然后前项遍历左子树，最后遍历右子树
    cout << "Preorder ptree_node value : " << ptree_node->item.Value << endl;
    PreorderTraversal(ptree_node->m_left); //递归访问左子树的左右节点
    PreorderTraversal(ptree_node->m_right);//递归访问右子树的左右节点

}


void InorderTraversal(const Tree_Node *ptree_node)
{
    if(ptree_node == nullptr){
        return;
    }

    //原则：先前项遍历左子树，然后访问根节点，最后遍历右子树
    InorderTraversal(ptree_node->m_left);
    cout << "Inorder ptree_node value : " << ptree_node->item.Value << endl;
    InorderTraversal(ptree_node->m_right);

}

void PostorderTraversal(const Tree_Node *ptree_node)
{
    if(ptree_node == nullptr){
        return;
    }

    //原则：先前项遍历左子树，然后遍历右子树，最后访问根节点
    PostorderTraversal(ptree_node->m_left);
    PostorderTraversal(ptree_node->m_right);
    cout << "Postorder ptree_node value : " << ptree_node->item.Value << endl;

}
