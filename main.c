
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#pragma mark - SWAP
void swap(int *a, int *b) {
    
    //swap the two value's pointer address, rather than just swap value copy
    //如果相同，则异或结果会为0.所以要避免
    if (*a != *b) {
        
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }

}

#pragma mark - DATASOURCE
void *randomArrayGeneration(int arrayToRandomGenerate[], int length, int max) {
    
    srand((unsigned)time(NULL));
    
    for (int i = 0; i < length; i ++) {

        arrayToRandomGenerate[i] = 1+rand()%max;
    }

    return 0;
}

#pragma mark - SORTs
//basic bubbleSort O(n^2)
void bubbleSort(int *arrayToSort, int startPos, int endPos) {
    
    //注意，这个排序方法，每一次的冒泡排序都会将最大的顶到最末端，所以每一次只用扫描i到n-i就好，扫描一次之后i++
    
    int numberOfValue = endPos - startPos + 1;
    
    for (int i = 0; i < numberOfValue; i ++) {
        
        for (int j = 1; j < numberOfValue - i ; j ++) {
            
            if (arrayToSort[j - 1] > arrayToSort[j]) {

                swap(&arrayToSort[j - 1], &arrayToSort[j]);
                
            }
        }
    }

}

//improved bubbleSort O(n)
void bubbleSortWithFlag(int *arrayToSort, int startPos, int endPos) {
 
    int numberOfValue = endPos - startPos + 1;
    
    int flag = 1;   //设置一个标志位来检测本次向后的检测是否有数据交换，如果没有，则表示已经有序了
    int k = 0;
    
    
    while (flag) {
        
        flag = 0;
        
        for (int j = 1; j < numberOfValue - k; j ++) {
            
            
            if (arrayToSort[j - 1] > arrayToSort[j]) {
                swap(&arrayToSort[j - 1], &arrayToSort[j]);
                flag = 1;
            }
        }
        
        
        k ++;
        
    }
    
}

//inserSort O(n) to O(n^2)
void insertSort(int *arrayToSort, int startPos, int endPos) {

    int numberOfValue = endPos - startPos + 1;
    
    int i, j;
    for (i = 1; i < numberOfValue; i ++) {
        
        if (arrayToSort[i] < arrayToSort[i - 1]) {
            
            //如果没有找到逆序对，说明到目前为止，前面的数列都是有序的
            //如果找到了逆序对
            int temp = arrayToSort[i];
            for (j = i - 1; j >=0 && arrayToSort[j] > temp; j --) {
                
                //在已经排序的队列中找到比它大的数
                //并且将这个数之后的所有位置后移
                
                arrayToSort[j + 1] = arrayToSort[j];
            }
            
            //插入j + 1的位置。为什么这里j + 1，因为上面执行之后j-- 了
            arrayToSort[j + 1] = temp;
        }
    }

}

//注意，O(nlogn)平均时间复杂度的算法有：快速、归并、希尔、堆

//shellSort O(nlogn) -  其实是分组插入排序，分组方式通过gap确定
void shellSort(int *arrayToSort, int startPos, int endPos) {
    
    int numberOfValue = endPos - startPos + 1;
    
    int gap = numberOfValue/2;  //初始值为2个一组，分为总数/2组
    int i,j;
    
    for (gap = gap; gap > 0; gap /= 2) {
        
        //前半段
        for (i = 0; i < gap; i ++) {
            
            //后半段
            for (j = gap + i; j < numberOfValue; j += gap) {
                
                if (arrayToSort[j + i] < arrayToSort[j + i - gap]) {
                    
                    swap(&arrayToSort[j - gap + i], &arrayToSort[j + i]);
                }
            }
        }
    }
}

//selectSort O(n^2)
void selectSort(int *arrayToSort, int startPos, int endPos) {

    int numberOfValue = endPos - startPos + 1;
    int i,j;
    int minValueIndex = 0;
    
    //以start为基准，start+1开始逐个扫描，加入最后，初始化的时候，无序区为start
    for (i = 0; i < numberOfValue; i ++) {
        
        minValueIndex = i;
        
        for(j = i + 1; j < numberOfValue; j ++) {
            
            if (arrayToSort[j] < arrayToSort[minValueIndex]) {
                minValueIndex = j;
            }
        }
        
        //找到最小值，放到无序区的开头
        swap(&arrayToSort[i], &arrayToSort[minValueIndex]);
        
    }
    
    
}

//quickSort O(nlogn), 如已经有序 O(n^2)
//挖坑代码
int adjustArray(int *arrayToSort, int startPos, int endPos) {

    int i = startPos;
    int j = endPos;
    int baseValue = arrayToSort[startPos];  //首先以第一个为基准
    
    while (i < j) {
        
        while (j > i && arrayToSort[j] >= baseValue) {
            j --;
        }   //跳过所有比baseValue大的
        
        if (j > i) {
            //找到比baseValue小的
            //swap(&arrayToSort[i], &arrayToSort[j]);
            arrayToSort[i] = arrayToSort[j];
            i ++;
        }
        
        while (i < j && arrayToSort[i] <= baseValue) {
            //跳过所有比baseValue小的
            i ++;
        }
        
        if (i < j) {
            //找到比baseValue大的
            //swap(&arrayToSort[i], &arrayToSort[j]);
            arrayToSort[j] = arrayToSort[i];
            j --;
        }

    }
    
    //回填baseValue
    arrayToSort[i] = baseValue;
    
    return i ;
}
//分治法代码
void quickSort(int *arrayToSort, int startPos, int endPos) {

    if (startPos < endPos) {
        
        //startPos >= endPos，表示已经扫描结束
        
        int basePos = adjustArray(arrayToSort, startPos, endPos);
        quickSort(arrayToSort, startPos, basePos - 1);
        quickSort(arrayToSort, basePos + 1, endPos);
    }

}


//heapSort
//重建堆函数, 用来在节点变化之后，重建小顶堆
void minHeapFixDown (int *arrayToSort, int node, int total) {
    
    int i = 2 * node + 1;  //左子节点
    int temp = arrayToSort[node];   //这个节点为父节点
    
    while(i < total){
        //遍历所有节点
        
        if (i + 1 < total && arrayToSort[i + 1] < arrayToSort[i]) {
            
            i ++;   //在左右子节点中寻找较小的，最后停下来的位置就是最小的那个数所在的位置
            
        }
        if (temp <= arrayToSort[i]) {
            
            //如果父节点比最小的子节点要小，则不用再调整，找到位置
            break;
        }
        
        //如果父节点比子节点要大，则把子节点上移替换父节点
        //arrayToSort[node] = arrayToSort[i];
        swap(&arrayToSort[node], &arrayToSort[i]);
        //接着往更深的地方遍历，锚点变为子节点
        node = i;
        i = 2 * node + 1;
    }
    
    //最终找到合适的位置
    arrayToSort[node] = temp;
    
}
//堆排序，其实很像一个选择排序 O(nlogn)
void minHeapSort(int *arrayToSort, int startPos, int endPos) {

    //原理就是认为最末端是有序部分，每一次交换a[0]和a[i]，然后将a[0...i]进行堆重建，那么最后a[i]就是最小的数，再i--
    //随着进行，有序部分越来越长，直到覆盖整个数组
    //很像选择排序，选择排序是从前面的无序序列中选择一个，放到有序序列末端
    int numberOfValue = endPos - startPos + 1;
    
    for (int i = numberOfValue - 1; i > 0; i --) {
        
        swap(&arrayToSort[i], &arrayToSort[0]);
        minHeapFixDown(arrayToSort, 0, i);
    }
}

#pragma mark - SEARCHs
//binary tree O(logn)
//insert node
typedef struct node {
    //二叉树节点
    
    int element;
    struct node *l_Child, *r_Child, *parent;

} BNode, BTree;

BNode* binaryTree_CreateNode(int nodeValue){
    
    BNode *node = (BNode *)malloc(sizeof(BNode));
    
    node->element = nodeValue;
    node->l_Child = NULL;
    node->r_Child = NULL;
    node->parent = NULL;
    
    return node;
    
}

void binaryTree_Insert(BTree *root, int nodeValue) {
    
    //insert node value into tree which root node is 'root'
    if (!root) {
        //如果为空树，则创建该插入点为根节点
        root = binaryTree_CreateNode(nodeValue);
        return;
    }
    
    if (root->element > nodeValue) {
        //如果插入值比跟节点小，进入左子树
        //如果左子树为空，则直接插入
        if (!root->l_Child) {
            
            BNode *newNode = binaryTree_CreateNode(nodeValue);
            root->l_Child = newNode;
            newNode->parent = root;
            return;
        }
        //否则插入左子树
        binaryTree_Insert(root->l_Child, nodeValue);

    }
    
    if (root->element <= nodeValue) {
        //如果插入值比跟节点大，进入右子树
        //如果右子树为空，则直接插入
        if (!root->r_Child) {
            
            BNode *newNode = binaryTree_CreateNode(nodeValue);
            root->r_Child = newNode;
            newNode->parent = root;
            return;
        }
        //否则插入右子树
        binaryTree_Insert(root->r_Child, nodeValue);
        
    }
    
    return;
}

void binaryTree_CreateTree(BTree *root, int *valueArray, int length) {
    
    for (int i = 0; i < length; i ++){
        
        binaryTree_Insert(root, valueArray[i]);
    }
         
    
}

//中序遍历打印
void binaryTree_OutputByMidSeq(BTree *root){
    
    if (root) {
        binaryTree_OutputByMidSeq(root->l_Child);
        printf("%d\n", root->element);
        binaryTree_OutputByMidSeq(root->r_Child);
    }
    return;
}


#pragma mark - MAIN
int main(int argc, const char * argv[]) {
    
    int a[10];
    randomArrayGeneration(a, 10, 100);
    
    BTree *rootOfTree = (BTree *)malloc(sizeof(BTree));
    
    //bubbleSort(a, 0, 9);
    //bubbleSortWithFlag(a, 0, 9);
    //insertSort(a, 0, 9);
    //shellSort(a, 0, 9);
    //selectSort(a, 0, 9);
    //quickSort(a, 0, 9);
    //minHeapSort(a, 0, 9);
    //minHeapFixDown(a, 0, 9);

    binaryTree_CreateTree(rootOfTree, a, 10);
    //binaryTree_OutputByMidSeq(rootOfTree);
    
//    for (int i = 0; i < 10; i ++) {
//        printf("%d, ", a[i]);
//    }

    return 0;
}



