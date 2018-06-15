//
//  One.cpp
//  0524
//
//  Created by dqh on 2018/5/24.
//  Copyright © 2018年 dqh. All rights reserved.
//

#include "One.hpp"
#include <string>

using namespace std;

class MyStr
{
private:
    char *name;
    int id;

public:
    int kk;
};




///////|-------- 3.数组中重复的数字 --------------|\\\\\\\\\

// 题目1
bool duplicate(int numbers[], int length, int *duplicate)
{
    if (numbers == NULL || length <= 0) {
        return false;
    }
    
    for (int i = 0; i < length; i++) {
        if (numbers[i] < 0 || numbers[i] > length - 1) {
            return false;
        }
    }
    
    for (int i = 0; i < length; i++) {
        while (numbers[i] != i) {
            if (numbers[i] == numbers[numbers[i]]) {
                *duplicate = numbers[i];
                return true;
            }
            int temp = numbers[i];
            numbers[i] = numbers[numbers[i]];
            numbers[temp] = temp;
        }
    }
    return false;
}

// 题目2
int countRange(int array[], int length, int start, int end)
{
    if (array == nullptr) {
        return 0;
    }
    int count = 0;
    
    for (int i = 0; i < length; i++) {
        if (array[i] >= start && array[i] <= end) {
            count++;
        }
    }
    return count;
}

int getDuplicate(int array[], int length)
{
    if (array == nullptr || length <= 0) {
        return -1;
    }
    int start = 1;
    int end = length - 1;
    
    while (end >= start) {
        int middle = ((end - start) >> 1) + start;
        int count = countRange(array, length, start, middle);
        
        if (end == start) {
            if (count > 1) {
                return start;
            } else {
                break;
            }
        }
        if (count > (middle - start + 1)) {
            end = middle;
        } else {
            start = middle + 1;
        }
    }
    return -1;
}

//|-------- 4.二维数组中的查找 --------------|\\\\\\\\\

bool findFromTwoArray(int *array, int rows, int cols, int number)
{
    if (array == nullptr || rows <= 0 || cols <= 0) {
        return false;
    }
    
    int indexRow = 0;
    int indexCol = cols - 1;
    
    while (indexRow < rows && indexCol >= 0) {
        if (number == array[indexRow * cols + indexCol]) {
            return true;
        }
        if (number > array[indexRow * cols + indexCol]) {
            indexRow++;
        } else {
            indexCol--;
        }
    }
    return false;
}

//|-------- 5.替换空格（在原来的字符串上修改） --------------|\\\\\\\\\

void replaceBlank(char *string, int length)
{
    if (string == nullptr || length < 0) {
        return;
    }
    
    int replacedLength = length;
    
    for (int i = 0; i < length; i++) {
        char temp = string[i];
        if (temp == ' ') {
            replacedLength += 2;
        }
    }
    
    int oldIndex = length - 1;
    int newIndex = replacedLength - 1;
    
    while (oldIndex >= 0 && newIndex >= 0) {
        char temp = string[oldIndex];
        if (temp == ' ') {
            string[newIndex] = '0';
            string[newIndex - 1] = '2';
            string[newIndex - 2] = '%';
            
            oldIndex--;
            newIndex -= 3;
            
        } else {
            string[newIndex] = string[oldIndex];
            oldIndex--;
            newIndex--;
        }
    }
}

//拓展题
void insertArrayBToArrayA(int *arraA, int lengthA, int *arrayB, int lengthB)
{
    if (arraA == nullptr || lengthA <= 0|| arrayB == nullptr || lengthB <= 0) {
        return;
    }
    
    int maxLength = lengthA + lengthB;
    
    int indexA = lengthA - 1;
    int indexB = lengthB - 1;
    int indexNew = maxLength - 1;
    
    while (indexNew >= 0) {
        if (indexA >= 0) {
            if (arraA[indexA] >= arrayB[indexB]) {
                arraA[indexNew] = arraA[indexA];
                indexA--;
            } else {
                arraA[indexNew] = arrayB[indexB];
                indexB--;
            }
        } else {
            arraA[indexNew] = arrayB[indexB];
            indexB--;
        }
        indexNew--;
    }
}

//|-------- 6.从尾到头打印链表 --------------|\\\\\\\\\

//栈实现
void printLsitReversingly_stack(ListNode* pHead)
{
    std::stack<ListNode *> nodes;
    
    ListNode* pNode = pHead;
    
    while (pNode != nullptr) {
        nodes.push(pNode);
        pNode = pNode -> m_pNext;
    }
    
    while (!nodes.empty()) {
        pNode = nodes.top();
        nodes.pop();
        printf("value = %d",pNode->m_value);
    }
}

//递归实现
void printLsitReversingly_recursive(ListNode* pHead)
{
    if (pHead == nullptr) {
        return;
    }
    if (pHead -> m_pNext != nullptr) {
        printLsitReversingly_recursive(pHead->m_pNext);
    }
    printf("value = %d\n",pHead->m_value);
}

//|-------- 7.重建二叉树 --------------|\\\\\\\\\


BinaryTreeNode* constructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder)
{
    int rootValue = startPreorder[0];
    BinaryTreeNode* rootNode = new BinaryTreeNode();
    rootNode->m_pLeft = nullptr;
    rootNode->m_pRight = nullptr;
    rootNode->m_value = rootValue;

    if (startPreorder == endPreorder) {
        if (startInorder == endInorder && *startPreorder == *startInorder) {
            return rootNode;
        } else {
            throw std::exception();
        }
    }
    
    int *inorderRootIndex = startInorder;
    int LeftTreeLength = 0;
    
    for (int i = 0; i < (endInorder - startInorder); i++) {
        
        if (*(startInorder+i) == rootValue) {
            break;
        }
        inorderRootIndex++;
        LeftTreeLength++;
    }
    
    if (*(startInorder + LeftTreeLength) != rootValue) {
        throw std::exception();
    }
    
    if (LeftTreeLength > 0) {
        rootNode -> m_pLeft = constructCore(startPreorder+1, startPreorder+LeftTreeLength, startInorder, inorderRootIndex - 1);
    }
    if (LeftTreeLength < endPreorder - startPreorder) {
        rootNode -> m_pRight = constructCore(startPreorder+LeftTreeLength+1, endPreorder, inorderRootIndex+1, endInorder);
    }
    
    return rootNode;
}

BinaryTreeNode* construct(int* preorder, int* inorder, int length)
{
    if (preorder == nullptr || inorder == nullptr || length <= 0) {
        return nullptr;
    }
    return constructCore(preorder, preorder+length-1, inorder, inorder+length-1);
}

//|-------- 8.二叉树的下一个节点 --------------|\\\\\\\\\

BinaryTreeNode* getNextInorder(BinaryTreeNode* pNode)
{
    if (pNode == nullptr) {
        return nullptr;
    }
    BinaryTreeNode *pNext = nullptr;
    
    //先判断有没有右子节点
    if (pNode->m_pRight != nullptr) {
        BinaryTreeNode *pRight = pNode->m_pRight;
        while (pRight->m_pLeft != nullptr) {
            pRight = pRight->m_pLeft;
        }
        pNext = pRight;
    } else {
        BinaryTreeNode *pCurrent = pNode;
        BinaryTreeNode *pParent = pNode->m_pParent;
        
        while (pParent != nullptr && pCurrent == pParent->m_pRight) {
            pCurrent = pParent;
            pParent = pCurrent->m_pParent;
        }
        pNext = pParent;
    }
    return pNext;
}

///////|-------- 9.用两个栈实现队列 --------------|\\\\\\\\\


template <typename T> class CQueue
{
public:
    CQueue(void);
    ~CQueue(void);
    
    void appendTail(const T& element);
    T delegeHead();
    
private:
    stack<T> stack1;
    stack<T> stack2;
};



template <typename T> void CQueue<T>::appendTail(const T &element)
{
    stack1.push(element);
}

template <typename T> T CQueue<T>::delegeHead()
{
    if (stack2.empty()) {
        if (stack1.size() > 0) {
            while (!stack1.empty()) {
                T temp = stack1.top();
                stack2.push(temp);
                stack1.pop();
            }
        }
    }
    if (stack2.size()>0) {
        T head = stack2.top();
        stack2.pop();
        return head;
    }
    
    return nullptr;
}

//拓展题

template <typename T> class CStack
{
public:
    CStack(void);
    ~CStack(void);
    
    void appendTail(const T& element);
    T delegeHead();
    
private:
    queue<T> queue1;
    queue<T> queue2;
};

template <typename T> void CStack<T>::appendTail(const T &element)
{
    queue1.push(element);
}

template <typename T> T CStack<T>::delegeHead()
{
    if (queue1.size() > 0) {
        while (!queue1.empty()) {
            T head = queue1.top();
            queue2.push(head);
            queue1.pop();
        }
    }
    if (queue2.size()>0) {
        T head = queue2.top();
        queue2.pop();
        return head;
    }
    return nullptr;
}


///////|-------- 10.斐波那契数列 --------------|\\\\\\\\\

//题目1
long long fibonacci(unsigned n)
{
    if (n < 2) {
        int results[2] = {0, 1};
        return results[n];
    }
    
    long long firstResult = 0;
    long long secondResult = 1;
    long long result = 0;
    
    for (int i = 2; i <= n; i++) {
        result = firstResult + secondResult;
        firstResult = secondResult;
        secondResult = result;
    }
    
    return result;
}

//题目2
long long steps(unsigned n)
{
    if (n <= 2) {
        int results[3] = {0, 1, 2};
        return results[n];
    }
    
    long long firstResult = 1;
    long long secondResult = 2;
    long long result = 0;
    
    for (int i = 2; i < n; i++) {
        result = firstResult + secondResult;
        firstResult = secondResult;
        secondResult = result;
    }
    
    return result;
}

//题目3
long long stepsTwo(unsigned n)
{
    return 1<<--n;
}

///////|-------- 11.旋转数组的最小数字 --------------|\\\\\\\\\

int getMin(int* array, int length)
{
    if (length <= 0 || array == nullptr) {
        return -1;
    }
    if (length == 1) {
        return *array;
    }
    
    int index1 = 0;
    int index2 = length - 1;
    int indexMid = index1;
    
    while (*(array+index1) >= *(array+index2)) {
        if (index2 - index1 == 1) {
            indexMid = index2;
            break;
        }
        
        indexMid = (index1 + index2) >> 1;
        
        if (array[index1] == array[index2] && array[indexMid] == array[index1]) {
            int result = array[index1];
            for (int i = index1; i < index2; i++) {
                if (result > array[i]) {
                    return array[i];
                }
            }
        }
        else if (*(array+indexMid) >= *(array+index1)) {
            index1 = indexMid;
        }
        else if (*(array+indexMid) <= *(array+index2)) {
            index2 = indexMid;
        }
    }
    return array[indexMid];
}

///////|-------- 12.矩阵中的路径 --------------|\\\\\\\\\

bool hasPathCore(const char* matrix, int rows, int cols, int row, int col, const char* str, int pathLength, bool* visited)
{
    if (str[pathLength] == '\0') {
        return true;
    }
    bool hasPath = false;
    
    if (row >= 0 && row < rows && col >= 0 && col <= cols && matrix[row*cols + col] == str[pathLength] && !visited[row*cols+col]) {
        pathLength++;
        visited[row*cols + col] = true;
        
        hasPath = hasPathCore(matrix, rows, cols, row, col - 1, str, pathLength, visited)
                || hasPathCore(matrix, rows, cols, row, col + 1, str, pathLength, visited)
                || hasPathCore(matrix, rows, cols, row - 1, col, str, pathLength, visited)
                || hasPathCore(matrix, rows, cols, row + 1, col, str, pathLength, visited);
        
        if (!hasPath) {
            pathLength--;
            visited[row*cols + col] = false;
        }
    }
    
    return hasPath;
}

bool hasPath(char* matrix, int rows, int cols, char* str)
{
    if (matrix == nullptr || rows < 1 || cols<1 || str == nullptr) {
        return false;
    }
    bool *visited = new bool(rows*cols);
    memset(visited, 0, rows*cols);
    
    int pathLength = 0;
    
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (hasPathCore(matrix, rows, cols, row, col, str, pathLength, visited)) {
                return true;
            }
        }
    }
    delete visited;
    return false;
}

///////|-------- 13.机器人的运动范围 --------------|\\\\\\\\\

int getDigiSum(int number)
{
    int sum = 0;
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

int movingCountCore(unsigned int threshold, int rows, int cols, int row, int col, bool* visited)
{
    int count = 0;
    if (row >= 0 && row < rows && col >= 0 && col < cols && !visited[row*cols+col] && getDigiSum(row)+getDigiSum(col) <= threshold) {
        visited[row*cols+col] = true;
        
        count = 1 + movingCountCore(threshold, rows, cols, row, col-1, visited)
                 + movingCountCore(threshold, rows, cols, row, col+1, visited)
                 + movingCountCore(threshold, rows, cols, row-1, col, visited)
                 + movingCountCore(threshold, rows, cols, row+1, col, visited);
    }
    return count;
}

int movingCount(unsigned int threshold, int rows, int cols)
{
    if (rows <= 0 || cols <= 0) {
        return 0;
    }
    
    bool *visited = new bool(rows * cols);
    memset(visited, 0, rows*cols);
    
    int count = movingCountCore(threshold, rows, cols, 0, 0, visited);
    delete visited;
    
    return count;
}

///////|-------- 14.剪绳子 --------------|\\\\\\\\\

//解法1

int maxProductAfterCutting_solution1(int length)
{
    if (length < 2) {
        return 0;
    } else if (length == 2) {
        return 1;
    } else if (length == 3) {
        return 2;
    }
    
    int* products = new int(length+1);
    products[0] = 0;
    products[1] = 1;
    products[2] = 2;
    products[3] = 3;
    
    int max = 0;

    for (int i = 4; i <= length; i++) {
        max = 0;
        
        for (int j = 1; j < i; j++) {
            if (products[j]*products[i-j] > max) {
                max = products[j]*products[i-j];
            }
        }
        products[i] = max;
    }
    return max;
}

// 解法2
int maxProductAfterCutting_solution2(int length)
{
    if (length < 1) {
        return 0;
    }
    if (length == 2) {
        return 1;
    }
    if (length == 3) {
        return 2;
    }
    
    int timeOf3 = length / 3;
    
    if (length - 3*timeOf3 == 1) {
        timeOf3--;
    }
    
    int timeOf2 = (length - 3*timeOf3) / 2;
    
    return (pow(3, timeOf3) * pow(2, timeOf2));
}

///////|-------- 15.二进制中1的个数 --------------|\\\\\\\\\

int numberOf1(long long number)
{
    int count = 0;
    unsigned long long flag = 1;
    
    while (flag) {
        if (number & flag) {
            count++;
        }
        flag = flag << 1;
    }
    return count;
}

//进阶解法
int updateNumberOf1(long long number)
{
    int count = 0;
    
    while (number) {
        number = number & (number - 1);
        count++;
    }
    return count;
}

///////|-------- 16.数值的整数次方 --------------|\\\\\\\\\

double Power(double base, int exponent)
{
    if (fabs(base-0.0) < 0.0000001 && exponent == 0) {
        throw exception();
    }
    unsigned int absExponent = exponent;
    if (exponent < 0) {
        absExponent = -exponent;
    }
    double result = 1.;
    for (int i = 0; i < absExponent; i++) {
        result = base * result;
    }
    
    if (exponent < 0) {
        result = 1 / result;
    }
    return result;
}

//进阶写法

double updatePower(double base, unsigned int exponent)
{
    if (exponent == 0) {
        return 1;
    }
    if (exponent == 1) {
        return base;
    }
    
    double result = updatePower(base, exponent >> 1);
    result *= result;
    
    if ((exponent & 1) == 1) {
        result *= base;
    }
    return result;
}

///////|-------- 17.打印从1到最大的n位数 --------------|\\\\\\\\\

bool increaseNumber(char* str)
{
    bool overFlow = false;
    bool nTakeOver = 0;
    unsigned long length = strlen(str);
    
    for (int i = int(length - 1); i >= 0; i--) {
        
        int nSum = str[i] - '0' + nTakeOver;
        nTakeOver = 0;
        
        if (i == length-1) {
            nSum++;
        }
        
        if (nSum >= 10) {
            if (i == 0) {
                overFlow = true;
            }
            nTakeOver = 1;
            nSum %= 10;
        }
        str[i] = nSum + '0';
    }
    return overFlow;
}

void printNumber(char* str)
{
    bool beginPrint = false;
    
    for (int i = 0; i < strlen(str); i++) {
        if (!beginPrint && str[i] - '0' != 0 ) {
            beginPrint = true;
        }
        if (beginPrint) {
            printf("%c",str[i]);
        }
    }
    printf("\n");
}

void printMaxNumber(unsigned int n)
{
    if (n <= 0) {
        return;
    }
    
    char *str = new char(n+1);
    memset(str, '0', n+1);
    str[n] = '\0';
    
    while (!increaseNumber(str)) {
        printNumber(str);
    }
}

// 递归解决
void printToMaxOfNDigitsCore(char *str, int length, int index)
{
    if (index == length) {
        printNumber(str);
        return;
    }
    for (int i = 0; i < 10; i++) {
        str[index] = i + '0';
        printToMaxOfNDigitsCore(str, length, index+1);
    }
}

void printToMaxOfNDigits(unsigned int n)
{
    if (n <= 0) {
        return;
    }
    
    char *str = new char(n+1);
    memset(str, '0', n+1);
    str[n] = '\0';
    
    for (int i = 0; i < 10; i++) {
        str[0] = i + '0';
        printToMaxOfNDigitsCore(str, n, 1);
    }
    
}

///////|-------- 18.删除链表节点 --------------|\\\\\\\\\

//题目1 在o(1)的时间内删除一个节点
void deleteNode(ListNode** pHeader, ListNode *pToBeDeleted)
{
    if (!pHeader || !pToBeDeleted) {
        return;
    }
    
    //当被删除节点的下一个节点不为空
    if (pToBeDeleted->m_pNext != nullptr) {
        ListNode *pNext = pToBeDeleted->m_pNext;
        pToBeDeleted->m_value = pNext->m_value;
        pToBeDeleted->m_pNext = pNext->m_pNext;
        
        delete pNext;
        pNext = nullptr;
    }
    //当头结点跟被删除的节点一样
    else if (*pHeader == pToBeDeleted) {
        *pHeader = nullptr;
    }
    //是尾节点
    else {
        ListNode *pCurrent = *pHeader;
        while (pCurrent->m_pNext != pToBeDeleted || pCurrent->m_pNext != nullptr) {
            pCurrent = pCurrent->m_pNext;
        }
        if (pCurrent->m_pNext == pToBeDeleted) {
            pCurrent->m_pNext = nullptr;
            delete pToBeDeleted;
            pToBeDeleted = nullptr;
        } else {
            throw exception();
        }
    }
}

//题目2 删除链表中重复的节点
void deleteDuplicateListNode(ListNode **pHead)
{
    if (pHead == nullptr || *pHead == nullptr) {
        return;
    }
    
    ListNode *preNode = nullptr;
    ListNode *pNode = *pHead;
    
    while (pNode != nullptr) {
        ListNode *pNext = pNode->m_pNext;
        bool needDelete = false;
        
        if (pNext != nullptr && pNode->m_value == pNext->m_value) {
            needDelete = true;
        }
        
        if (!needDelete) {
            preNode = pNode;
            pNode->m_pNext = pNext;
            pNode = pNext;
        } else {
            ListNode *pToDelete = pNode;
            int value = pNode->m_value;
            
            while (pNext != nullptr && pNext->m_value == value) {
                pNext = pNext->m_pNext;
                
                delete pToDelete;
                pToDelete = nullptr;
                
                pToDelete = pNext;
            }
            
            if (preNode == nullptr) {
                *pHead = pNext;
            } else {
                preNode->m_pNext = pNext;
            }
            pNode = pNext;
        }
    }
}


///////|-------- 19.正则表达式匹配 --------------|\\\\\\\\\

bool matchPatternCore(char* str, char* pattern)
{
    if (*str == '\0' && *pattern == '\0') {
        return true;
    }
    if (*str != '\0' && *pattern == '\0') {
        return false;
    }
    
    if (*(pattern+1) == '*') {
        if ((*pattern) == (*str) || ((*pattern == '.') && (*str) != '\0')) {
            return matchPatternCore(str+1, pattern+2) || matchPatternCore(str, pattern+2) || matchPatternCore(str+1, pattern+2);
        } else {
            return matchPatternCore(str, pattern+2);
        }
    }
    
    if ((*pattern) == (*str) || (*pattern) == '.') {
        return matchPatternCore(str+1, pattern+1);
    }
    
    return false;
}

bool matchPattern(char* str, char* pattern)
{
    if (str == nullptr || pattern == nullptr) {
        return false;
    }
    return matchPatternCore(str, pattern);
}

///////|-------- 20.表示数值的字符串 --------------|\\\\\\\\\

bool scanUnsignedInteger(const char** str)
{
    const char* before = *str;
    while (**str != '\0' && **str >= '0' && **str <= '9') {
        (*str)++;
    }
    return (*str) > before;
}

bool scanInteger(const char** str)
{
    if (**str == '+' || **str == '-') {
        (*str)++;
    }
    return scanUnsignedInteger(str);
}

bool isNumeric(const char* str)
{
    if (str == nullptr || *str == '\0') {
        return false;
    }

    //整数部分
    bool numeric = scanInteger(&str);
    

    //有小数点
    if (*str == '.') {
        str++;
        
        /*
         * 下面一行代码用||的原因：
         * 1. 小数后面可以没有整数部分 如.12.等于0.12
         * 2. 小数点后面没有数字，如12.等于12.0
         * 3. 小数点前面和后面都可以有数字 如12.12
         */
        
        numeric = numeric || scanUnsignedInteger(&str);
    }
    
    if (*str == 'E' || *str == 'e') {
        str++;
        /*
         * 下面一行代码用&&的原因
         * 1. 当E或者e前面没有数字时，整个字符串不能表示为数字， 例如.e1, e1
         * 2. 当E或者e后面没有整数是，整个字符串不能表示为数字， 例如12e， 12e+5.4
         */
        numeric = numeric && scanInteger(&str);
    }
    
    return numeric && (*str) == '\0';
}

///////|-------- 21.调整数组顺序使奇数位于偶数前面 --------------|\\\\\\\\\

void reorderOddEvent(int* array, int length)
{
    if (array == nullptr || length <= 1) {
        return;
    }
    
    int* start = array;
    int* end = array + length - 1;
    
    while (end > start) {
        while (((*start) & 1) == 1) {
            start++;
        }
        
        while (((*end) & 1) == 0) {
            end--;
        }
        
        if (end > start) {
            int temp = *start;
            *start = *end;
            *end = temp;
            
            start++;
            end--;
        }
    }
    
    for (int i = 0; i < length; i++) {
        printf("%d \n",*(array+i));
    }
}

///////|-------- 22.链表中倒数第K个节点 --------------|\\\\\\\\\

ListNode* findLastKNode(ListNode* pHead, int k)
{
    if (pHead == nullptr || k <= 0) {
        return nullptr;
    }
    
    ListNode *pNode = pHead;
    ListNode *pPre = pHead;
    
    for (int i = 0; i < k; i++) {
        pNode++;
        if (pNode == nullptr && i != k-1) {
            throw exception();
        }
    }
    
    while (pNode->m_pNext != nullptr) {
        pNode = pNode->m_pNext;
        pPre = pPre->m_pNext;
    }
    
    return pPre;
}

// 拓展题
ListNode* findMiddleNodeFromList(ListNode* pHead)
{
    if (pHead == nullptr) {
        return nullptr;
    }
    
    ListNode* pAhead = nullptr;
    ListNode* pBehind = nullptr;
    
    if (pHead->m_pNext->m_pNext != nullptr) {
        pAhead = pHead->m_pNext->m_pNext;
        pBehind = pHead->m_pNext;
    } else {
        return pHead->m_pNext;
    }
    
    while (pAhead != nullptr) {
        pBehind = pBehind->m_pNext;
        
        pAhead = pAhead->m_pNext;
        if (pAhead != nullptr) {
            pAhead = pAhead->m_pNext;
        }
    }
    return pBehind;
}


///////|-------- 23.链表中环的入口节点 --------------|\\\\\\\\\


ListNode* findEntranceNode(ListNode* pHead)
{
    if (pHead == nullptr) {
        return nullptr;
    }
    
    ListNode* p1 = pHead;//一次走一步
    ListNode* p2 = pHead;//一次走两步
    if (p2->m_pNext != nullptr) {
        p2 = p2->m_pNext;
    } else {
        return nullptr;
    }
    
    while (p1 != nullptr && p1 != p2) {
        p1 = p1->m_pNext;
        
        p2 = p2->m_pNext;
        if (p2 != nullptr) {
            p2 = p2->m_pNext;
        }
    }
    
    //没有环
    if (p1 == nullptr) {
        return nullptr;
    }
    
    //在环中相遇的点
    ListNode* meetNode = p1;
    //环的长度
    int circleLength = 0;
    
    p1 = p1->m_pNext;
    while (p1 != meetNode) {
        p1 = p1->m_pNext;
        circleLength++;
    }
    
    //找入口点
    p1 = pHead;
    p2 = pHead;
    
    for (int i = 0; i < circleLength; i++) {
        p2++;
    }
    while (p1 != p2) {
        p1 = p1->m_pNext;
        p2 = p2->m_pNext;
    }
    return p1;
}

///////|-------- 24.反转链表 --------------|\\\\\\\\\

ListNode* reverseList(ListNode* pHead)
{
    if (pHead == nullptr) {
        return nullptr;
    }
    if (pHead->m_pNext == nullptr) {
        return pHead;
    }
    
    ListNode* pPre = nullptr;
    ListNode* pNode = pHead;
    ListNode* pNext = pHead->m_pNext;
    ListNode* reverseListHead = nullptr;
    
    while (pNode != nullptr) {
        reverseListHead = pNode;
        reverseListHead->m_pNext = pPre;
        
        pNode = pNext;
        if (pNext != nullptr) {
            pNext = pNext->m_pNext;
        }
    }
    
    return reverseListHead;
}

///////|-------- 25.合并两个排序的链表 --------------|\\\\\\\\\

void sortTwoIncreaseList(ListNode* list1, ListNode* list2)
{
    if (list1 == nullptr || list2 == nullptr) {
        return;
    }

    ListNode* p1 = list1;
    ListNode* p2 = list2;
    ListNode* pNode = nullptr;
    
    if (p1->m_value <= p2->m_value) {
        pNode = p1;
        p1 = p1->m_pNext;
    } else {
        pNode = p2;
        p2 = p2->m_pNext;
    }
    
    while (p1 != nullptr || p2 != nullptr) {
        if (p1 != nullptr && p2 != nullptr) {
            if (p1->m_value <= p2->m_value) {
                pNode -> m_pNext = p1;
                p1 = p1->m_pNext;
            } else {
                pNode -> m_pNext = p2;
                p2 = p2->m_pNext;
            }
        } else if (p1 == nullptr) {
            pNode -> m_pNext = p2;
            p2 = p2->m_pNext;
        } else if (p2 == nullptr) {
            pNode -> m_pNext = p1;
            p1 = p1->m_pNext;
        }
        pNode = pNode->m_pNext;
    }
}

///////|-------- 26.树的子结构 --------------|\\\\\\\\\

bool doesTree1HaveTree2Core(BinaryTreeNode* tree1, BinaryTreeNode* tree2)
{
    if (tree2 == nullptr) {
        return true;
    }
    if (tree1 == nullptr) {
        return false;
    }
    
    if (tree1->m_value != tree2->m_value) {
        return false;
    }
    return doesTree1HaveTree2Core(tree1->m_pLeft, tree2->m_pLeft) && doesTree1HaveTree2Core(tree1->m_pRight, tree2->m_pRight);
}


bool doesTree1HaveTree2(BinaryTreeNode* tree1, BinaryTreeNode* tree2)
{
    if (tree1 == nullptr) {
        return false;
    }
    if (tree2 == nullptr) {
        return true;
    }
    bool result = false;
    
    if (tree1->m_value == tree2->m_value) {
        result = doesTree1HaveTree2Core(tree1,tree2);
    } else {
        result = doesTree1HaveTree2(tree1->m_pLeft,tree2) || doesTree1HaveTree2(tree1->m_pRight,tree2);
    }
    return result;
}


///////|-------- 27.二叉树的镜像 --------------|\\\\\\\\\

void mirrorTree(BinaryTreeNode* pTree)
{
    if (pTree == nullptr) {
        return;
    }

    BinaryTreeNode* temp = pTree->m_pLeft;
    pTree->m_pLeft = pTree->m_pRight;
    pTree->m_pLeft = temp;
    
    mirrorTree(pTree->m_pLeft);
    mirrorTree(pTree->m_pRight);
}


///////|-------- 28.对称的二叉树 --------------|\\\\\\\\\

bool isSymmetryTreeCore(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    if (pRoot1 == nullptr && pRoot2 == nullptr) {
        return true;
    }
    if (pRoot1 == nullptr || pRoot2 == nullptr) {
        return false;
    }
    
    return isSymmetryTreeCore(pRoot1->m_pLeft,pRoot2->m_pRight) && isSymmetryTreeCore(pRoot1->m_pRight,pRoot2->m_pLeft);
}


bool isSymmetryTree(BinaryTreeNode* pTree)
{
    if (pTree == nullptr) {
        return false;
    }
    
    return isSymmetryTreeCore(pTree, pTree);
}

///////|-------- 29.顺时针打印矩阵 --------------|\\\\\\\\\

void clockPrintRectCore(int* array, int rows, int cols, int count)
{
    if (array == nullptr || rows < 0 || cols < 0 || (count*2 > rows || count*2 > cols)) {
        return;
    }
    
    int rowIndex = count;
    int colIndex = count;
    
    
    //左上到右上 0，3
    printf("%d\n",*(rowIndex*cols + colIndex + array));

    while (colIndex < cols - count - 1) {
        colIndex++;
        printf("%d\n",*(rowIndex*cols + colIndex + array));
    }
    
    while (rowIndex < rows - count - 1) {
        rowIndex++;
        printf("%d\n",*(rowIndex*cols + colIndex + array));
    }

    while (colIndex > count && (rows-2*count - 1) != 0) {
        colIndex--;
        printf("%d\n",*(rowIndex*cols + colIndex + array));
    }
    
    while (rowIndex > count && (cols-2*count - 1) != 0) {
        rowIndex--;
        printf("%d\n",*(rowIndex*cols + colIndex + array));
    }
    
    clockPrintRectCore(array, rows, cols, count+1);
}

void clockPrintRect(int* array, int rows, int cols)
{
    if (array == nullptr || rows<0 || cols<0) {
        return;
    }
    clockPrintRectCore(array, rows, cols, 0);
}


///////|-------- 30.包含min函数的栈 --------------|\\\\\\\\\

template <typename T> class DStack
{
public:
    DStack(void);
    ~DStack(void);
    
    void push(const T& element);
    void pop();
    T min();
    
private:
    stack<T> stack1;
    stack<T> stack2;
};

template <typename T> void DStack<T>::push(const T &element)
{
    if (stack1.empty()) {
        stack1.push(element);
        stack2.push(element);
    } else {
        int min = (int)stack2.top();
        if (min < (int)element) {
            stack2.push(min);
        } else {
            stack2.push(element);
        }
        stack1.push(element);
    }
}

template <typename T> void DStack<T>::pop()
{
    if (stack1.empty() || stack2.empty()) {
        return;
    }
    stack1.pop();
    stack2.pop();
}

template <typename T> T DStack<T>::min()
{
    if (stack2.empty()) {
        return nullptr;
    }
    return stack2.top();
}


///////|-------- 31.栈的压入、弹出序列 --------------|\\\\\\\\\

bool isPopOrder(int* push, int* pop, int length)
{
    if (push == nullptr || pop == nullptr) {
        return false;
    }
    
    stack<int> stackPush;

    int* pushIndex = push;
    
    for (int i = 0; i < length; i++) {
        int temp = *(pop + i);
        
        while (stackPush.empty() || stackPush.top() != temp) {
            if (pushIndex - push >= length) {
                return false;
            }
            stackPush.push(*pushIndex);
            pushIndex++;
        }
        stackPush.pop();
    }
    return true;
}

///////|-------- 32.从上到下打印二叉树 --------------|\\\\\\\\\

//题目1 不分行从上到下打印二叉树
void printTreeFormTopToBottom(BinaryTreeNode* pRoot)
{
    //用两个队列实现
    if (pRoot == nullptr) {
        return;
    }
    std::queue<BinaryTreeNode*> queueOne;
    std::queue<BinaryTreeNode*> queueTwo;
    
    queueOne.push(pRoot);
    
    
    while (!queueOne.empty() || !queueTwo.empty()) {
        if (queueOne.empty() && !queueTwo.empty()) {
            
            while (!queueTwo.empty()) {
                BinaryTreeNode* pTree = queueTwo.front();
                if (pTree != nullptr) {
                    printf("%d ",pTree->m_value);
                    if (pTree->m_pLeft != nullptr) {
                        queueOne.push(pTree->m_pLeft);
                    }
                    if (pTree->m_pRight != nullptr) {
                        queueOne.push(pTree->m_pRight);
                    }
                    queueTwo.pop();
                }
            }
        }
        else if (queueTwo.empty() && !queueOne.empty()) {
            
            while (!queueOne.empty()) {
                BinaryTreeNode* pTree = queueOne.front();
                if (pTree != nullptr) {
                    printf("%d ",pTree->m_value);
                    if (pTree->m_pLeft != nullptr) {
                        queueTwo.push(pTree->m_pLeft);
                    }
                    if (pTree->m_pRight != nullptr) {
                        queueTwo.push(pTree->m_pRight);
                    }
                    queueOne.pop();
                }
            }
        }
    }
}

//题目2 分行从上到下打印二叉树
void linePrintTreeFormTopToBottom(BinaryTreeNode* pRoot)
{
    //用两个queue实现
    if (pRoot == nullptr) {
        return;
    }
    std::queue<BinaryTreeNode*> queueOne;
    std::queue<BinaryTreeNode*> queueTwo;
    
    queueOne.push(pRoot);
    
    
    while (!queueOne.empty() || !queueTwo.empty()) {
        if (queueOne.empty() && !queueTwo.empty()) {
            
            while (!queueTwo.empty()) {
                BinaryTreeNode* pTree = queueTwo.front();
                if (pTree != nullptr) {
                    printf("%d ",pTree->m_value);
                    if (pTree->m_pLeft != nullptr) {
                        queueOne.push(pTree->m_pLeft);
                    }
                    if (pTree->m_pRight != nullptr) {
                        queueOne.push(pTree->m_pRight);
                    }
                    queueTwo.pop();
                }
            }
            printf("\n");
        }
        else if (queueTwo.empty() && !queueOne.empty()) {
            
            while (!queueOne.empty()) {
                BinaryTreeNode* pTree = queueOne.front();
                if (pTree != nullptr) {
                    printf("%d ",pTree->m_value);
                    if (pTree->m_pLeft != nullptr) {
                        queueTwo.push(pTree->m_pLeft);
                    }
                    if (pTree->m_pRight != nullptr) {
                        queueTwo.push(pTree->m_pRight);
                    }
                    queueOne.pop();
                }
            }
            printf("\n");
        }
    }
}

// 题目3 之字形打印二叉树
void zPrintTreeFormTopToBottom(BinaryTreeNode* pRoot)
{
    //用两个queue实现
    if (pRoot == nullptr) {
        return;
    }
    std::stack<BinaryTreeNode*> stackOne;
    std::stack<BinaryTreeNode*> stackTwo;
    
    stackOne.push(pRoot);
    
    
    while (!stackOne.empty() || !stackTwo.empty()) {
        if (stackOne.empty() && !stackTwo.empty()) {
            
            while (!stackTwo.empty()) {
                BinaryTreeNode* pTree = stackTwo.top();
                if (pTree != nullptr) {
                    printf("%d ",pTree->m_value);
                    if (pTree->m_pRight != nullptr) {
                        stackOne.push(pTree->m_pRight);
                    }
                    if (pTree->m_pLeft != nullptr) {
                        stackOne.push(pTree->m_pLeft);
                    }
                    stackTwo.pop();
                }
            }
            printf("\n");
        }
        else if (stackTwo.empty() && !stackOne.empty()) {
            
            while (!stackOne.empty()) {
                BinaryTreeNode* pTree = stackOne.top();
                if (pTree != nullptr) {
                    printf("%d ",pTree->m_value);
                    if (pTree->m_pLeft != nullptr) {
                        stackTwo.push(pTree->m_pLeft);
                    }
                    if (pTree->m_pRight != nullptr) {
                        stackTwo.push(pTree->m_pRight);
                    }
                    stackOne.pop();
                }
            }
            printf("\n");
        }
    }
}

///////|-------- 33.二叉搜索树的后序遍历序列 --------------|\\\\\\\\\

bool isOutOrderList(int* array, int length)
{
    if (array == nullptr || length <= 0) {
        return false;
    }
    
    int root = array[length-1];
    int rightStartIndex = length-1;
    
    for (int i = 0; i < length-1; i++) {
        if (*(array+i) > root) {
            rightStartIndex = i;
            break;
        }
    }

    for (int i = rightStartIndex; i < length-1; i++) {
        if (*(array+i) < root) {
            return false;
        }
    }
    
    bool left = true;
    bool right = true;
    
    if (rightStartIndex > 0) {
        left = isOutOrderList(array, rightStartIndex);
    }
    if (rightStartIndex < length - 1) {
        right = isOutOrderList(array+rightStartIndex, length - 1 - rightStartIndex);
    }
    
    return (left && right);
}

///////|-------- 34.二叉树中和为某一值的所有路径 --------------|\\\\\\\\\

void findPathCore(BinaryTreeNode* pRoot, int totalSum, int currentSum, vector<BinaryTreeNode*> &path)
{
    if (pRoot == nullptr) {
        return;
    }
    
    bool isLeaf = pRoot->m_pLeft == nullptr && pRoot -> m_pRight == nullptr;
    int rootValue = pRoot->m_value;
    currentSum += rootValue;
    path.push_back(pRoot);
    
    if (currentSum == totalSum && isLeaf) {
        std::vector<BinaryTreeNode*>::iterator iter = path.begin();
        while (iter != path.end()) {
            BinaryTreeNode* pTree = *iter;
            printf("%d ",pTree->m_value);
            iter++;
        }
        printf("\n");
    }
    
    if (pRoot->m_pLeft != nullptr) {
        findPathCore(pRoot->m_pLeft, totalSum, currentSum,path);
    }
    if (pRoot->m_pRight != nullptr) {
        findPathCore(pRoot->m_pRight, totalSum, currentSum,path);
    }
    path.pop_back();
}

void findPath(BinaryTreeNode* pRoot, int totalSum)
{
    
    if (pRoot == nullptr || totalSum < 0) {
        return;
    }
    std::vector<BinaryTreeNode*> path;
    int currentSum = 0;
    
    return findPathCore(pRoot, totalSum,currentSum,path);
}

///////|-------- 35.复杂链表的复制 --------------|\\\\\\\\\

ListNode* cloneComplexList(ListNode* pHead)
{
    if (pHead == nullptr) {
        return nullptr;
    }
    if (pHead->m_pNext == nullptr) {
        ListNode *pNewHeader = new ListNode();
        pNewHeader->m_value = pHead->m_value;
        pNewHeader->m_pNext = nullptr;
        pNewHeader->m_pSibling = nullptr;
        return pNewHeader;
    }
    
    ListNode *pNode = pHead;
    
    //在原来的链表中复制一份，原链表 1>2>3>4 新链表1>1>2>2>3>3>4>4
    while (pNode != nullptr) {
        ListNode* pNew = new ListNode();
        pNew->m_value = pNode->m_value;
        pNew->m_pNext = pNode->m_pNext;
        pNew->m_pSibling = nullptr;
        
        ListNode *pNext = pNode->m_pNext;
        pNode->m_pNext = pNew;
        pNew->m_pNext = pNext;
        pNode = pNext;
    }
    
    //对新加进去的节点的m_pSibling赋值
    ListNode *pNewList = pHead;
    while (pNewList != nullptr) {
        ListNode* pOld = pNewList;
        ListNode* pNew = pOld->m_pNext;
        
        if (pOld->m_pSibling != nullptr) {
            pNew->m_pSibling = pOld->m_pSibling->m_pNext;
        }
        pNewList = pNew->m_pNext;
    }
    
    //将新加进去的节点分离，并且连接成一个链表
    ListNode* pTemp = pHead;
    ListNode* pNewHead = pHead->m_pNext;
    
    while (pTemp != nullptr) {
        ListNode* pOld = pTemp;
        ListNode* pNew = pOld->m_pNext;
        
        pOld->m_pNext = pNew->m_pNext;
        if (pOld->m_pNext != nullptr) {
            pNew->m_pNext = pOld->m_pNext->m_pNext;
        }
        
        pTemp = pOld->m_pNext;
    }
    
    
    return pNewHead;
}



///////|-------- 36.二叉搜索树与双向链表 --------------|\\\\\\\\\

void convertCore(BinaryTreeNode* pRoot, BinaryTreeNode** pLastOfNodeList)
{
    if (pRoot == nullptr) {
        return;
    }
    
    BinaryTreeNode* pCurrent = pRoot;
    
    //中序遍历
    if (pCurrent->m_pLeft != nullptr) {
        convertCore(pRoot->m_pLeft, pLastOfNodeList);
    }
    
    pCurrent->m_pLeft = *pLastOfNodeList;
    if (*pLastOfNodeList != nullptr) {
        (*pLastOfNodeList)->m_pRight = pCurrent;
    }
    *pLastOfNodeList = pCurrent;
    
    if (pCurrent->m_pRight != nullptr) {
        convertCore(pRoot->m_pRight, pLastOfNodeList);
    }
}

BinaryTreeNode* convert(BinaryTreeNode* pRoot)
{
    if (pRoot == nullptr) {
        return nullptr;
    }
    
    BinaryTreeNode* pLastOfList = nullptr;
    convertCore(pRoot, &pLastOfList);
    
    while (pLastOfList != nullptr && pLastOfList->m_pLeft != nullptr) {
        pLastOfList = pLastOfList->m_pLeft;
    }
    
    return pLastOfList;
}

///////|-------- 37.序列化二叉树 --------------|\\\\\\\\\

//序列化

void serialize(BinaryTreeNode* pRoot,ostream& stream)
{
    if (pRoot == nullptr) {
        stream << "$,";
        return;
    }
    stream << pRoot->m_value << ',';
    serialize(pRoot->m_pLeft, stream);
    serialize(pRoot->m_pRight, stream);
}

//反序列化

void deserialize(BinaryTreeNode** pRoot, istream& stream)
{
//    int number;
//    if (stream.re) {
//
//    }
}


///////|-------- 38.字符串的排列 --------------|\\\\\\\\\

void printAllPermutationCore(char* strings, int length, int start)
{
    if (strings == nullptr || length == 0) {
        return;
    }
    if (strings[start] == '\0') {
        printf("%s\n",strings);
        return;
    }
    
    for (int i = start; i < length-1; i++) {
        char temp = strings[start];
        strings[start] = strings[i];
        strings[i] = temp;
        
        printAllPermutationCore(strings, length, start+1);
        
        temp = strings[start];
        strings[start] = strings[i];
        strings[i] = temp;
    }
}

void printAllPermutation(char* strings, int length)
{
    if (strings == nullptr || length <= 0) {
        return;
    }
    printAllPermutationCore(strings, length, 0);
}

// 拓展题1

void printAllPermutationOneCore(char* strings, int length, int start, int newLength, char* newStr)
{
    if (newLength == 0) {
        printf("%s\n",newStr);
        return;
    }
    
    //i代表组合长度
    for (int j = start; j < length; j++) {
        
        newStr[start] = strings[j];
        printAllPermutationOneCore(strings, length, start+1, newLength-1, newStr);
        newStr[start] = ' ';
        
        printAllPermutationOneCore(strings, length, start+1, newLength, newStr);
    }
}


void printAllPermutationOne(char* strings, int length)
{
    if (strings == nullptr || length <= 0) {
        return;
    }
    
    char aa[length+1];
    memset(aa, ' ', length);
    aa[length] = '\0';
    
    for (int i = 0; i < length+1; i++) {
        printAllPermutationOneCore(strings, length, 0, i, aa);
    }
}

// 拓展题2

bool printAllPermutationCoreTwo(int* array, int length, int start)
{
    if (array == nullptr || length == 0) {
        return false;
    }
    if ((array[0]+array[1]+array[2]+array[3] == array[4]+array[5]+array[6]+array[7])
        && (array[0]+array[2]+array[4]+array[6] == array[1]+array[3]+array[5]+array[7])
        && (array[0]+array[1]+array[4]+array[5] == array[2]+array[3]+array[6]+array[7]))
    {
        return true;
    }
    for (int i = start; i < length-1; i++) {
        int temp = array[start];
        array[start] = array[i];
        array[i] = temp;
        
        printAllPermutationCoreTwo(array, length, start+1);
        
        temp = array[start];
        array[start] = array[i];
        array[i] = temp;
    }
    return false;
}

void printAllPermutationTwo(int* array, int length)
{
    if (array == nullptr || length <= 0) {
        return;
    }
    bool result = printAllPermutationCoreTwo(array, length, 0);
    printf("%d\n",result);
}

// 拓展题3

int printAllPermutationThreeCore(int* array, int length, int startIndex)
{
    if (startIndex >= length) {
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                //判断是否在同一对角线上
                if ((i != j) && ((j == array[j] && (i == array[i])) || ((j == length - array[j]) && (i == length - array[i])))) {
                    return 0;
                }
            }
        }
        return 1;
    }
    
    int count = 0;
    
    for (int  i = startIndex; i < length; i++) {
        int temp = array[startIndex];
        array[startIndex] = array[i];
        array[i] = temp;
        
        count += printAllPermutationThreeCore(array, length, startIndex+1);
        
        temp = array[startIndex];
        array[startIndex] = array[i];
        array[i] = temp;
    }
    return count;
}

int printAllPermutationThree(int length)
{
    if (length <= 0) {
        return 0;
    }
    
    int columIndex[length];
    for (int i = 0; i < length; i++) {
        columIndex[i] = i;
    }
    
    return printAllPermutationThreeCore(columIndex, length, 0);
}

///////|-------- 39.数组中出现次数超过一半的数字 --------------|\\\\\\\\\

int myPartition(int* array, int length, int start, int end)
{
    if (array == nullptr || length <= 0) {
        throw exception();
    }
    if (start == end) {
        return start;
    }
    
    int smallIndex = start - 1;
    
    int temp = array[end];
    array[end] = array[start];
    array[start] = temp;
    
    for (int i = start; i < end; i++) {
        if (array[i] < array[end]) {
            smallIndex++;
            if (smallIndex != i) {
                temp = array[i];
                array[i] = array[smallIndex];
                array[smallIndex] = temp;
            }
        }
    }
    smallIndex++;
    temp = array[end];
    array[end] = array[smallIndex];
    array[smallIndex] = temp;
    
    return smallIndex;
}

int moreThanHalf(int* numbers, int length)
{
    if (numbers == nullptr || length <= 0) {
        return -1;
    }
    int start = 0;
    int end = length - 1;
    int middle = (length - 1) >> 1;
    int index = myPartition(numbers, length, start, end);
    
    while (index != middle) {
        
        if (middle > index) {
            start = index + 1;
            index = myPartition(numbers, length, start, end);
        }
        if (middle < index) {
            end = index - 1;
            index = myPartition(numbers, length, start, end);
        }
    }
    return (numbers[(length-1) >> 1]);
}

///////|-------- 40.最小的k个数 --------------|\\\\\\\\\

//解法1 使用快排的思路
void minestNumbers(int* array, int length, int k)
{
    if (array == nullptr || length <= 0 || k > length) {
        return;
    }
    
    int start = 0;
    int end = length - 1;
    int index = myPartition(array, length, start, end);
    
    while (index != k) {
        if (index > k) {
            break;
        }
        if (index < k) {
            index = myPartition(array, length, index+1, end);
        }
    }
    for (int i = 0; i < k; i++) {
        printf("%d ",array[i]);
    }
    printf("\n");
}

//解法2


///////|-------- 41.数据流中的中位数 --------------|\\\\\\\\\

template <typename T> class DynamicArray
{
private:
    vector<T> min;
    vector<T> max;
    
public:
    void insert(T num)
    {
        if (((min.size() + max.size()) & 1) == 0) {
            if (max.size() > 0 && num < max[0]) {
                max.push_back(num);
                push_heap(max.begin(), max.end(), less<T>());
                
                num = max[0];
                
                pop_heap(max.begin(), max.end(), less<T>());
                max.pop_back();
            }
            min.push_back(num);
            push_heap(min.begin(), min.end(), greater<T>());
        }
        else {
            if (min.size() > 0 && min[0] < num) {
                min.push_back(num);
                push_heap(min.begin(), min.end(), greater<T>());
                
                num = min[0];
                
                pop_heap(min.begin(), min.end(), greater<>());
                min.pop_back();
            }
            max.push_back(num);
            push_heap(max.begin(), max.end(), less<T>());
        }
    }
    
    T getMedia()
    {
        int size = min.size() + max.size();
        if (size == 0) {
            throw exception();
        }
        T media = 0;
        if ((size & 1) == 1) {
            media = min[0];
        } else {
            media = (min[0] + max[0]) / 2;
        }
        return media;
    }
};

///////|-------- 42.连续子数组的最大和 --------------|\\\\\\\\\

int findGreatestSumOfSubArray(int* array, int length)
{
    if (array == nullptr || length <= 0) {
        return 0;
    }
    int max = 0;
    int sum = 0;
    
    for (int i = 0; i < length; i++) {
        sum += array[i];
        if (sum > max) {
            max = sum;
        }
        if (sum <= 0) {
            sum = 0;
        }
    }
    return max;
}

///////|-------- 43.1~n整数中1的出现的次数 --------------|\\\\\\\\\

int powerBase10(unsigned int n)
{
    int result = 1;
    for (int i = 0; i < n; i++) {
        result *= 10;
    }
    return result;
}

int numberOf1Between1AndNCore(char* str)
{
    if (str == nullptr || *str < '0' || *str > '9' || *str == '\0') {
        return 0;
    }
    
    int first = *str - '0';
    unsigned int length = static_cast<unsigned int>(strlen(str));
    
    if (first == 0 && length == 0) {
        return 0;
    }
    if (first != 0 && length == 1) {
        return 1;
    }
    
    // 分成两部分。如果传进来的数字为89757，则分成1 ~ 9757和9758 ~ 89757两部分
    //最高位有多少1
    int numberFirstDigit = 0;
    
    if (first > 1) {
        numberFirstDigit = powerBase10(length - 1);
    } else if (first == 1) {
        numberFirstDigit = atoi(str + 1) + 1;
    }
    
    //其它位上有多少1
    int numberOfOtherDigit = first * (length - 1) * powerBase10(length - 2);
    
    
    int numRecursive = numberOf1Between1AndNCore(str + 1);
    
    return numberFirstDigit + numberOfOtherDigit + numRecursive;
}

int numberOf1Between1AndN(int n)
{
    if (n <= 0) {
        return 0;
    }
    if (n < 10) {
        return 1;
    }
    char str[50];
    sprintf(str, "%d", n);
    
    return numberOf1Between1AndNCore(str);
}

///////|-------- 44.数字序列中某一位的数字 --------------|\\\\\\\\\

int getTheIndexDigit(int number, int index)
{
    for (int i = 0; i < index - 1; i++) {
        number /= 10;
    }
    return number %= 10;
}

int digitAtIndex(int index)
{
    if (index < 0) {
        throw exception();
    }
    // 如果只有1位
    if (index < 10) {
        return index;
    }
    //找出这是几位数，至少两位
    int numberOfDigit = 2;
    index -= 10;
    
    while (index > numberOfDigit * (powerBase10(numberOfDigit) - powerBase10(numberOfDigit-1))) {
        index -= numberOfDigit * (powerBase10(numberOfDigit) - powerBase10(numberOfDigit-1));
        numberOfDigit++;
    }
    int currentNumber = 0;
    int result = 0;
    if (index % numberOfDigit == 0) {
        //是当前数字的最后一位
        currentNumber = powerBase10(numberOfDigit-1) + index/numberOfDigit - 1 ;
        result = getTheIndexDigit(currentNumber, numberOfDigit);
    } else {
        //是当前数字的余数位
        currentNumber = powerBase10(numberOfDigit-1) + index/numberOfDigit - 1 + 1;
        result = getTheIndexDigit(currentNumber, index%numberOfDigit);
    }
    
    
    return result;
}

///////|-------- 45.把数组排成最小的数 --------------|\\\\\\\\\

const int g_maxNumberLength = 10;

char* g_strCombin1 = new char[2*g_maxNumberLength + 1];
char* g_strCombin2 = new char[2*g_maxNumberLength + 1];

int compare(const void* strNumber1, const void* strNumber2)
{
    strcpy(g_strCombin1, *(const char**)strNumber1);
    strcpy(g_strCombin1, *(const char**)strNumber2);
    
    strcpy(g_strCombin2, *(const char**)strNumber1);
    strcpy(g_strCombin2, *(const char**)strNumber2);

    return strcmp(g_strCombin1, g_strCombin2);
}

void printMinNumber(int* numbers, int length)
{
    if (numbers == nullptr || length <= 0) {
        return;
    }
    
    //将数组中的每个数字转换成字符串保存在strNumbers数组中
    char** strNumbers = (char**)(new int[length]);
    for (int i = 0; i < length; i++) {
        strNumbers[i] = new char[g_maxNumberLength + 1];
        sprintf(strNumbers[i], "%d", numbers[i]);
    }
    
    //排序
    qsort(strNumbers, length, sizeof(char*), compare);
    
    
    for (int i = 0; i < length; i++) {
        printf("%s",strNumbers[i]);
    }
    printf("\n");
}


///////|-------- 46.把数字翻译成字符串 --------------|\\\\\\\\\

int getTranslationCountCore(const string& numberString)
{
    int length = (int)numberString.length();
    int* counts = new int[length];
    int count = 0;
    
    for (int i = length - 1; i >= 0; i--) {
        count = 0;
        if (i < length - 1) {
            count = counts[i+1];
        }
        else {
            count = 1;
        }
        
        if (i < length - 1) {
            int digit1 = numberString[i] - '0';
            int digit2 = numberString[i + 1] - '0';
            int converd = digit1*10 + digit2;
            
            if (converd >= 10 && converd <= 26) {
                if (i < length - 2) {
                    count += counts[i+2];
                } else {
                    count += 1;
                }
            }
        }
        counts[i] = count;
    }
    count = counts[0];
    return count;
}

int getTranslationCount(int number)
{
    if (number <= 0) {
        return 0;
    }
    string numberString = to_string(number);
    
    return getTranslationCountCore(numberString);
}

///////|-------- 47.礼物的最大价值 --------------|\\\\\\\\\

int getMaxValue(int* values, int rows, int cols)
{
    if (values == nullptr || rows <= 0 || cols <= 0) {
        return 0;
    }
    int** maxVlaue = new int*[rows];
    for (int i = 0; i < rows; i++) {
        maxVlaue[i] = new int[cols];
    }
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            
            int left = 0;
            int up = 0;
            
            if (j > 0) {
                left = maxVlaue[i][j-1];
            }
            if (i > 0) {
                up = maxVlaue[i-1][j];
            }
            
            maxVlaue[i][j] = max(left, up) + values[i*cols + j];
        }
    }
    return maxVlaue[rows-1][cols-1];
}

///////|-------- 48.最长不含重复字符的子字符串 --------------|\\\\\\\\\

int longestLengthOfSubString(std::string str)
{
    if (str.length() == 0) {
        return 0;
    }
    // 保存 以第i个字符结尾的最长不含重复字符的字符串长度
    int* maxLengths = new int[str.length()];
    memset(maxLengths, -1, str.length());
    int maxResult = 0;
    
    for (int i = 0; i < str.length(); i++) {
        
        int temp = 0;
        char currentLetter = str[i];
        
        if (i > 0) {
            for (int j = i-1; j >= 0; j--) {
                char preLetter = str[j];
                if (currentLetter == preLetter) {
                    temp = i - j;
                    break;
                }
            }
        }
        if (temp == 0) {
            // 前面没有重复的字母
            maxLengths[i] = i > 0 ? maxLengths[i-1] + 1 : 1;
        }
        else if (temp > maxLengths[i - 1]) {
            
            maxLengths[i] = i > 0 ? maxLengths[i-1] + 1 : 1;
        }
        else if (temp <= maxLengths[i - 1]) {
            maxLengths[i] = temp;
        }
        if (maxLengths[i] > maxResult) {
            maxResult = maxLengths[i];
        }
    }
    return maxResult;
}

///////|-------- 49.丑数 --------------|\\\\\\\\\


int getUglyNumber(int index)
{
    if (index <= 0) {
        return 0;
    }
    
    int* numbers = new int[index];
    memset(numbers, 0, index);
    numbers[0] = 1;
    
    
    int currentIndex = 1;
    
    int* pMultiply2 = numbers;
    int* pMultiply3 = numbers;
    int* pMultiply5 = numbers;

    while (currentIndex < index) {
        int min = 0;
        min = (*pMultiply2)*2 < (*pMultiply3)*3 ? (*pMultiply2)*2 : (*pMultiply3)*3;
        min = min < (*pMultiply5)*6 ? min : (*pMultiply5)*5;
        
        numbers[currentIndex] = min;
        
        while ((*pMultiply2)*2 <= min) {
            pMultiply2++;
        }
        while ((*pMultiply3)*3 <= min) {
            pMultiply3++;
        }
        while ((*pMultiply5)*5 <= min) {
            pMultiply5++;
        }
    
        currentIndex++;
    }
    
    return numbers[index-1];
}


///////|-------- 50.第一次只出现一次的字符 --------------|\\\\\\\\\

// 题目1 字符串中第一个只出现一次的字符

char findNotRepeatChar(char* str)
{
    if (str == nullptr) {
        return '\0';
    }
    int hashTable[256];
    for (int i = 0; i < 256; i++) {
        hashTable[i] = 0;
    }
    char* pString = str;
    
    while (*pString != '\0') {
        char temp = *pString;
        hashTable[temp] = hashTable[temp] + 1;
        pString++;
    }

    pString = str;
    while (*pString != '\0') {
        char temp = *pString;
        if (hashTable[temp] == 1) {
            return temp;
        }
        pString++;
    }
    
    return '\0';
}

// 相关题1

void deleteAllString2CharInString1(char* string1, char* string2)
{
    if (string1 == nullptr || string2 == nullptr) {
        return;
    }
    int hashTable[256];
    for (int i = 0; i < 256; i++) {
        hashTable[i] = 0;
    }
    
    char* pString = string2;
    
    while (*pString != '\0') {
        char temp = *pString;
        hashTable[temp] = hashTable[temp] + 1;
        pString++;
    }
    
    pString = string1;
    while (*pString != '\0') {
        char temp = *pString;
        if (temp != ' ') {
            if (hashTable[temp] > 0) {
                
            } else {
                printf("%c",temp);
            }
        } else {
            printf(" ");
        }
        pString++;
    }
    printf("\n");
}

//  相关题2
void deleteRepeatCahr(char* string)
{
    if (string == nullptr) {
        return;
    }
    int hashTable[256];
    memset(hashTable, 0, 256*sizeof(int));
    
    char* pString = string;
    
    while (*pString != '\0') {
        char temp = *pString;
        hashTable[temp] = hashTable[temp] + 1;
        
        if (hashTable[temp] == 1) {
            printf("%c",temp);
        }
        pString++;
    }
    printf("\n");
}

// 相关题3
bool isAnagram(char* str1, char* str2)
{
    if (str1 == nullptr || str2 == nullptr) {
        return false;
    }
    int hashTable[256];
    memset(hashTable, 0, 256*sizeof(int));
    
    char* pString = str1;
    while (*pString != '\0') {
        char temp = *pString;
        hashTable[temp] = hashTable[temp] + 1;
        pString++;
    }
    
    pString = str2;
    while (*pString != '\0') {
        char temp = *pString;
        hashTable[temp] = hashTable[temp] - 1;
        pString++;
    }
    
    for (int i = 0; i < 256; i++) {
        if (hashTable[i] != 0) {
            return false;
        }
    }
    return true;
}

// 题目2

class ChatStaistics {
  
private:
    int occurrence[256];
    int index;

    
public:
    ChatStaistics():index(0) {
        for (int i = 0; i < 256; i++) {
            occurrence[i] = -1;
        }
    }
    
    void Insert(char ch)
    {
        if (occurrence[ch] == -1) {
            occurrence[ch] = index;
        } else if (occurrence[ch] > 0) {
            occurrence[ch] = -2;
        }
        index++;
    }
    
    char FirstAppearingOnce()
    {
        char ch = '\0';
        int minIndex = numeric_limits<int>::max();
        for (int i = 0; i < 256; i++) {
            if (occurrence[i] >= 0 && occurrence[i] < minIndex) {
                ch = (char)i;
                minIndex = occurrence[i];
            }
        }
        return ch;
    }
};


///////|-------- 51.数组中的逆序对 --------------|\\\\\\\\\

int inverseParisCore(int* data, int* copy, int start, int end)
{
    if (start == end) {
        copy[start] = copy[end];
        return 0;
    }
    int length = (end - start) >> 1;
    
    int left = inverseParisCore(data, copy, start, start+length);
    int right = inverseParisCore(copy, data, start+length+1, end);
    
    //i初始化为前半段最后一个数字的下标
    int i = start + length;
    //j初始化为后半段最后一个数字的下标
    int j = end;
    
    int indexCopy = end;
    int count = 0;
    
    while (i >= start && j >= start+length+1) {
        if (data[i] > data[j]) {
            copy[indexCopy] = data[i];
            count += j - start - length;
            indexCopy--;
            i--;
        } else {
            copy[indexCopy] = data[j];
            indexCopy--;
            j--;
        }
    }
    
    for (; i >= start; i--) {
        copy[indexCopy] = data[i];
        indexCopy--;
    }
    for (; j >= start+length+1; j--) {
        copy[indexCopy] = data[j];
        indexCopy--;
    }
    
    return left + right + count;
}

int inverseParis(int* data, int length)
{
    if (data == nullptr || length <= 0) {
        return 0;
    }
    int* copy = new int[length];
    for (int i = 0; i < length; i++) {
        copy[i] = data[i];
    }
    
    return inverseParisCore(data, copy, 0, length - 1);
}

///////|-------- 52.两个链表的第一个公共节点 --------------|\\\\\\\\\

unsigned int getListLength(ListNode* pHead)
{
    if (pHead == nullptr) {
        return 0;
    }
    ListNode* pNode = pHead;
    unsigned int length = 0;
    
    while (pNode != nullptr) {
        pNode = pNode -> m_pNext;
        length++;
    }
    return length;
}

ListNode* findFirstCommonNode(ListNode* pHead1, ListNode* pHead2)
{
    if (pHead1 == nullptr || pHead2 == nullptr) {
        return nullptr;
    }
    
    unsigned int nLength1 = getListLength(pHead1);
    unsigned int nLength2 = getListLength(pHead1);

    ListNode* pNodeLong = pHead1;
    ListNode* pNodeShort = pHead2;
    int lengthDif = nLength1 - nLength2;
    
    if (nLength1 < nLength2) {
        pNodeLong = pHead2;
        pNodeShort = pHead1;
        lengthDif = nLength2 - nLength1;
    }

    //长的链表先走几步
    for (int i = 0; i < lengthDif; i++) {
        pNodeLong = pNodeLong -> m_pNext;
    }
    
    while (pNodeLong != nullptr && pNodeShort != nullptr && pNodeShort != pNodeLong) {
        pNodeLong = pNodeLong -> m_pNext;
        pNodeShort = pNodeShort -> m_pNext;
    }
    
    if (pNodeLong != nullptr && pNodeShort != nullptr) {
        return pNodeLong;
    } else {
        throw exception();
    }    
}




