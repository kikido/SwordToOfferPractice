//
//  One.hpp
//  0524
//
//  Created by dqh on 2018/5/24.
//  Copyright © 2018年 dqh. All rights reserved.
//

#ifndef One_hpp
#define One_hpp

#include <stdio.h>
#include <iostream>
#include<string>
#include <limits>
#include <string>
#include <stack>
#include <queue>
#include <math.h>
#include <fstream>

struct BinaryTreeNode
{
    int m_value;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
    BinaryTreeNode* m_pParent;
};

struct ListNode
{
    int m_value;
    ListNode* m_pNext;
    ListNode* m_pSibling;
};

bool duplicate(int numbers[], int length, int *duplicate);

int getDuplicate(int array[], int length);

bool findFromTwoArray(int *array, int rows, int cols, int number);

void replaceBlank(char *string, int length);

void insertArrayBToArrayA(int *arraA, int lengthA, int *arrayB, int lengthB);

BinaryTreeNode* construct(int* preorder, int* inorder, int length);

long long steps(unsigned n);

long long stepsTwo(unsigned n);

int getMin(int* array, int length);

bool hasPath(char* matrix, int rows, int cols, char* str);

int movingCount(unsigned int threshold, int rows, int cols);

int maxProductAfterCutting_solution1(int length);

int maxProductAfterCutting_solution2(int length);

int numberOf1(long long number);

int updateNumberOf1(long long number);

double Power(double base, int exponent);

double updatePower(double base, unsigned exponent);

void printMaxNumber(unsigned int n);

void printToMaxOfNDigits(unsigned int n);

void deleteDuplicateListNode(ListNode **pHead);

bool matchPattern(char* str, char* pattern);

bool isNumeric(const char* str);

void reorderOddEvent(int* array, int length);

void sortTwoIncreaseList(ListNode* list1, ListNode* list2);

void clockPrintRect(int* array, int rows, int cols);

bool isPopOrder(int* push, int* pop, int length);

void printTreeFormTopToBottom(BinaryTreeNode* pRoot);

void linePrintTreeFormTopToBottom(BinaryTreeNode* pRoot);

void zPrintTreeFormTopToBottom(BinaryTreeNode* pRoot);

bool isOutOrderList(int* array, int length);

void findPath(BinaryTreeNode* pRoot, int totalSum);

ListNode* cloneComplexList(ListNode* pHead);

BinaryTreeNode* convert(BinaryTreeNode* pRoot);

void printAllPermutation(char* strings);

void printAllPermutationOne(char* strings, int length);

void printAllPermutationTwo(int* array, int length);

int printAllPermutationThree(int length);

int moreThanHalf(int* numbers, int length);

void minestNumbers(int* array, int length, int k);

int findGreatestSumOfSubArray(int* array, int length);

int numberOf1Between1AndN(int n);

int digitAtIndex(int index);

void printMinNumber(int* numbers, int length);

int longestLengthOfSubString(std::string str);

int getUglyNumber(int index);

char findNotRepeatChar(char* str);

void deleteAllString2CharInString1(char* string1, char* string2);

void deleteRepeatCahr(char* string);

bool isAnagram(char* str1, char* str2);
#endif /* One_hpp */
