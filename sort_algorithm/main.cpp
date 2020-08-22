#include <iostream>
#include <vector>
using namespace std;


//排序算法的类型：
//你想一下，查找下标和对象赋值是两个概念，每一个算法的特点可以从哪些方面可以分析
//1.基本概念，实现步骤,
//性能如何？时间复杂度和空间复杂度怎么样？稳定程度怎么样？是什么原因造成的不稳定
//使用场景如何？
//有哪些分类？
//具体实现是怎么样的？
//如何选择适合当前应用场景的算法？





//编写交换函数
void Swap(int & value1, int & value2)
{
    int temp_value = 0;  //临时存放变量值

    temp_value = value1;
    value1 = value2;
    value2 = temp_value;
}


//冒泡排序算法的定义：
//使用限制是什么? 性能如何？
//写好每一个算法的实现步骤
void BubbleSort(vector<int> & value)
{
    for(size_t i = 0;  i < value.size() - 1; i++){
        for(size_t j = 0;  j < value.size() - 1 - i; j ++){ //每次会运算会把最大值放在最后，所以没有必要遍历到最后一个值，所以-i
            if(value[j] > value[j + 1]){
                Swap(value[j],value[j + 1]);
            }else{
                continue;
            }
        }
    }
}

//选择排序算法Selection Sort
void SelectionSort(vector<int> & value)
{
    size_t min_position = 0; //存放当前最小值的下标位置

    for(size_t i = 0;  i < value.size() - 1; i++){
        min_position = i;
        for(size_t j = i + 1;  j < value.size(); j ++){
            if(value[min_position] > value[j]){
              min_position = j;
              break; //一旦找到对应的值，立刻退出这一层for循环，不然影响效率
            }
        }
        Swap(value[i], value[min_position]);
    }
}


//插入排序算法
void InsertionSort(vector<int> & value)
{
    int prev_position = 0; //保存前一项的位置,
    int current_value = 0; //保存当前元素的值

    //从第一项开始，第0项为初始值
    for(size_t i = 1; i < value.size(); i++){
        prev_position = i - 1;
        current_value = value[i]; //先保存当前的值
        //while循环的作用是通过遍历找到当前值所要存放的位置.每一次都和前面的项比，如果当前项的值小于前一项的值，继续往前，直到比完第0项停止
        while((current_value < value[prev_position]) && (prev_position >= 0)){ //大于等于0的原因是也要和第0项比较
            //前一项的值往后移，
            value[prev_position + 1] = value[prev_position];
            prev_position--;
        }
        value[prev_position + 1] =  current_value;
    }
}


//希尔排序算法，没有看懂，需要其他资料协助

//归并排序算法，分治（divide-and-conquer）策略,可以使用递归函数吗？ 非递归函数的算法实现怎么写？类似平衡二叉树,冷静一下，我居然写不出来？？？？
//这个处理有问题

void Conquer(vector<int> & value, int start_position, int middle_position, int end_position, vector<int> &  tmp_value)
{

}

void Divide(vector<int> & value, int start_position, int end_position, vector<int> & tmp_value)
{

    int middle_position = (end_position + start_position) / 2;
    //这个判断的作用是什么？先切割成最小单元再进行排序
    if(start_position < end_position){
        Divide(value, start_position, middle_position, tmp_value);
        Divide(value, middle_position + 1, end_position, tmp_value);
        Conquer(value, start_position, middle_position, end_position, tmp_value);
    }else{
        return;
    }
}


void MergeSort(vector<int> & value)
{
    vector<int> tmp_value;

    Divide(value, 0, value.size(), tmp_value);

    value = tmp_value;
}



//Divide函数的作用是什么？划分出小于基准的元素和大于基准的元素，并返回基准的坐标
int  QuickSortDivide(vector<int> & value, int start_position, int end_position)
{
    int temp_value = 0;
    int reference_position = start_position - 1; //为什么要-1？
    int reference_value = value[end_position]; //我选择的起始点作为基准点，和选择结束点作为基准点有什么不同,选择结束点作为基准点,数组从左到右开始遍历,选择起始点作为基准点，数组从右到到开始遍历，

    //遍历区间内的值，做什么处理? 与基准值比较，要是小于基准值就放在左边，记录基准值的位置
    for(int i = start_position;  i < end_position; i++){
        if(value[i] < reference_value){
            //既然当前位置i的值小于基准值，那么小于基准值的个数肯定会增加，位置也会变化
            reference_position++;

            //小于基准值的时候，为什么要交换，交换什么？把大于基准值的位置替换成当前位置的值，注意当reference_position == i,只是自己替换自己
            temp_value = value[reference_position];
            value[reference_position] = value[i];
            value[i] = temp_value;
        }else{
            continue;
        }
    }

    //循环结束之后，把基准点值放到小于基准的元素和大于基准的元素之间，并返回当前基准点的位置
    temp_value = value[reference_position + 1];
    value[reference_position + 1] = value[end_position];
    value[end_position] = temp_value;

    return reference_position + 1;
}


//快速排序算法（Quick Sort）
void QuickSort(vector<int> & value,int start_position, int end_position)
{

    //需要建立的临时变量有哪些
    //1.选择一个基准值，（一般选择什么为基准值？第一个或者最后一个。还有如果是等于基准的值呢？放在哪一边都可以）将所有数值进行排序，将会得到两个部分，一个是小于基准的数组，另外一个是大于基准的数组
    //2.使用递归的方式，将此步骤继续进行，（什么判断条件下结束）
    int position = 0;
    if (start_position < end_position){
        position = QuickSortDivide(value, start_position, end_position);//返回划分元素的最终位置
        QuickSort(value,start_position,position-1);//划分左边递归
        QuickSort(value, position + 1,end_position);//划分右边递归
    }
}


//计数排序
void CountingSort(vector<int> & value, int  MaxValue)
{

}


int main()
{

    vector<int> value;

    vector<int> BubbleValue;
    vector<int> SelectionValue;
    vector<int> InsertionValue;
    vector<int> MergeSortValue;
    vector<int> QuickSortValue;

    for(int i = 0; i < 5; i++){
        value.push_back(rand());
    }
    vector<int>::iterator it;
    cout << "original value : ";
    for(it = value.begin(); it < value.end(); it ++){
        cout << (*it) << ", ";
    }

    BubbleValue = value;
    BubbleSort(BubbleValue);
    cout << endl;
    cout << "BubbleSort value : ";
    for(it = BubbleValue.begin(); it < BubbleValue.end(); it ++){
        cout << (*it) << ", ";
    }

    SelectionValue = value;
    SelectionSort(SelectionValue);
    cout << endl;
    cout << "SelectionSort value : ";
    for(it = SelectionValue.begin(); it < SelectionValue.end(); it ++){
        cout << (*it) << ", ";
    }

    InsertionValue = value;
    InsertionSort(InsertionValue);
    cout << endl;
    cout << "InsertionSort value : ";
    for(it = InsertionValue.begin(); it < InsertionValue.end(); it ++){
        cout << (*it) << ", ";
    }

    MergeSortValue = value;
    MergeSort(MergeSortValue);
    cout << endl;
    cout << "MergeSort value : ";
    for(it = MergeSortValue.begin(); it < MergeSortValue.end(); it ++){
        cout << (*it) << ", ";
    }

    QuickSortValue = value;
    //[ 41, 6334, 26500, 18467, 19169, ]
//    QuickSortValue.push_back(41);
//    QuickSortValue.push_back(6334);
//    QuickSortValue.push_back(26500);
//    QuickSortValue.push_back(18467);
//    QuickSortValue.push_back(19169);
    QuickSort(QuickSortValue,0,4);
    cout << endl;
    cout << "QuickSort value : ";
    for(it = QuickSortValue.begin(); it < QuickSortValue.end(); it ++){
        cout << (*it) << ", ";
    }
    return 0;
}
