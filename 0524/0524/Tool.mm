//
//  Tool.m
//  0524
//
//  Created by dqh on 2018/5/24.
//  Copyright © 2018年 dqh. All rights reserved.
//

#import "Tool.h"
#include "One.hpp"


struct oc_listNode
{
    NSInteger m_value;
    oc_listNode* m_pNext;
};



@implementation Tool

#pragma mark - 3.数组中重复的数字

//第一题
- (BOOL)duplicate:(NSMutableArray *)array duplicateNumber:(NSInteger *)duplicate
{
    if (!array || array.count <= 0) {
        return NO;
    }
    for (NSInteger i = 0; i < array.count; i++) {
        if ([array[i] integerValue] < 0 || [array[i] integerValue] > array.count - 1) {
            return NO;
        }
    }
    for (NSInteger i = 0; i < array.count; i++) {
        while ([array[i] integerValue] != i) {
            NSInteger temp = [array[i] integerValue];
            if (temp == [array[temp] integerValue]) {
                *duplicate = temp;
                return YES;
            }
            array[i] = array[temp];
            array[temp]  = @(temp);
        }
    }
    return NO;
}

//第二题
- (NSInteger)getDuplicate:(NSMutableArray *)array
{
    if (!array || array.count <= 0) {
        return -1;
    }
    
    NSInteger start = 1;
    NSInteger end = array.count - 1;
    
    while (end >= start) {
        
        NSInteger middle = ((end - start) >> 1) + start;
        NSInteger count = [self countRange:array start:start end:middle];
        
        if (start == end) {
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


- (NSInteger)countRange:(NSMutableArray *)array start:(NSInteger)start end:(NSInteger)end
{
    if (!array || array.count <= 0) {
        return 0;
    }
    NSInteger count = 0;
    for (NSInteger i = 0; i < array.count; i++) {
        if ([array[i] integerValue] >= start && [array[i] integerValue] <= end) {
            count++;
        }
    }
    return count;
}

#pragma mark - 4.二维数组中的查找


- (BOOL)findFromArray:(NSArray *)array number:(NSInteger)number
{
    if (!array || array.count == 0) {
        return NO;
    }
    
    NSInteger rows = [array count];
    NSInteger cols = 0;
    if ([array.firstObject isKindOfClass:[NSArray class]]) {
        cols = [array.firstObject count];
    } else {
        return NO;
    }
    
    NSInteger rowIndex = 0;
    NSInteger colsIndex = cols - 1;
    
    while (colsIndex >= 0 && rowIndex < rows) {
        if (number == [array[rowIndex][colsIndex] integerValue]) {
            return YES;
        }
        if (number > [array[rowIndex][colsIndex] integerValue]) {
            rowIndex++;
        } else {
            colsIndex--;
        }
    }
    return false;
}

#pragma mark - 6.从尾到头打印链表

- (void)printLsitReversingly_recursive:(oc_listNode *)pHead
{
    if (pHead == nullptr) {
        return;
    }
    if (pHead->m_pNext != nullptr) {
        [self printLsitReversingly_recursive:pHead->m_pNext];
    }
    NSLog(@"value = %ld",pHead->m_value);
}

#pragma mark - 7.重建二叉树

- (Oc_BinaryTreeNode *)construct:(NSArray *)preorder inorder:(NSArray *)inorder
{
    if (!preorder || !inorder || preorder.count == 0 || preorder.count != inorder.count) {
        throw [NSException exceptionWithName:NSInvalidArgumentException reason:@"无效的参数" userInfo:nil];
    }
    
    return [self constructCore:preorder inorder:inorder startPreorder:0 endPreorder:preorder.count-1 startInorder:0 endInorder:inorder.count-1];
}


- (Oc_BinaryTreeNode *)constructCore:(NSArray *)preorder
                             inorder:(NSArray *)inorder
                       startPreorder:(NSInteger)startPreorder
                         endPreorder:(NSInteger)endPreorder
                        startInorder:(NSInteger)startInorder
                          endInorder:(NSInteger)endInorder
{
    if (!preorder || !preorder || endPreorder >= preorder.count || endInorder >= inorder.count) {
        throw [NSException exceptionWithName:NSInvalidArgumentException reason:@"无效的参数" userInfo:nil];
    }
    
    NSInteger rootValue = [preorder[startPreorder] integerValue];
    Oc_BinaryTreeNode *rootNode = new Oc_BinaryTreeNode();
    rootNode->m_value = rootValue;
    rootNode->m_pLeft = nullptr;
    rootNode->m_pRight = nullptr;
    
    if (startPreorder == endPreorder) {
        if (startInorder == endInorder && [preorder[startPreorder] integerValue] == [inorder[startInorder] integerValue]) {
            return rootNode;
        } else {
            throw [NSException exceptionWithName:NSInvalidArgumentException reason:@"无效的参数" userInfo:nil];
        }
    }
    
    NSInteger rootInorderIndex = startInorder;
    
    for (NSInteger i = startInorder; i < endInorder; i++) {
        
        if ([inorder[i] integerValue] == rootValue) {
            break;
        }
        rootInorderIndex++;
    }

    NSInteger leftLength = rootInorderIndex - startInorder;

    if (leftLength == (endInorder - startInorder)) {
        if ([inorder[endInorder] integerValue] != rootValue) {
            throw [NSException exceptionWithName:NSInvalidArgumentException reason:@"无效的参数" userInfo:nil];
        }
    }
    
    
    if (leftLength > 0) {
        rootNode->m_pLeft = [self constructCore:preorder inorder:inorder startPreorder:startPreorder+1 endPreorder:startPreorder+leftLength startInorder:startInorder endInorder:rootInorderIndex-1];
    }
    if (leftLength < (endPreorder - startPreorder)) {
        rootNode->m_pRight = [self constructCore:preorder inorder:inorder startPreorder:startPreorder + leftLength + 1 endPreorder:endPreorder startInorder:rootInorderIndex+1 endInorder:endInorder];
    }
    
    return rootNode;
}

#pragma mark - 8.二叉树的下一个节点

- (Oc_BinaryTreeNode *)nextNodeInorder:(Oc_BinaryTreeNode *)pNode
{
    if (pNode == nullptr) {
        return nullptr;
    }
    Oc_BinaryTreeNode* pNext = nullptr;
    
    if (pNode -> m_pRight != nullptr) {
        Oc_BinaryTreeNode* pRight = pNode->m_pRight;
        while (pRight && pRight->m_pLeft != nullptr) {
            pRight = pRight->m_pLeft;
        }
        pNext = pRight;
    }
    else if (pNode->m_pParent != nullptr) {
        Oc_BinaryTreeNode *pParent = pNode->m_pParent;
        Oc_BinaryTreeNode *pCurrent = pNode;
        
        while (pParent != nullptr && pCurrent == pParent->m_pRight) {
            pCurrent = pParent;
            pParent = pCurrent->m_pParent;
        }
        pNext = pParent;
    }
    return pNext;
}

#pragma mark - 11.旋转数组的最小数字
- (NSInteger)getMin:(NSArray *)array
{
    if (!array || array.count == 0) {
        return -1;
    }
    if (array.count == 1) {
        return [array.firstObject integerValue];
    }
    
    NSInteger index1 = 0;
    NSInteger index2 = array.count - 1;
    NSInteger indexMid = index1;
    
    while ([array[index1] integerValue] >= [array[index2] integerValue]) {
        if (index2 - index1 == 1) {
            indexMid = index2;
            break;
        }
        indexMid = ((index2 - index1) >> 1) + index1;
            
        if ([array[index1] integerValue] == [array[index2] integerValue] && [array[index1] integerValue] == [array[indexMid] integerValue]) {
            NSInteger result = [array[index1] integerValue];
            for (NSInteger i = index1; i < index2; i++) {
                if (result > [array[i] integerValue]) {
                    return [array[i] integerValue];
                }
            }
        }
        else if ([array[indexMid] integerValue] >= [array[index1] integerValue]) {
            index1 = indexMid;
        }
        else if ([array[indexMid] integerValue] <= [array[index2] integerValue]) {
            index2 = indexMid;
        }
    }
    return [array[indexMid] integerValue];
}

#pragma mark - 12.矩阵中的路径

- (BOOL)haspath:(NSArray *)matrix str:(NSString *)str
{
    if (str.length <= 0 || !matrix || matrix.count == 0) {
        return NO;
    }
    
    if (![matrix.firstObject isKindOfClass:[NSArray class]]) {
        return false;
    }
    NSInteger rows = matrix.count;
    NSInteger cols = [matrix.firstObject count];
    NSInteger pathLength = 0;
    
    bool *visited = new bool(rows * cols);
    memset(visited, 0, rows*cols);
    
    for (NSInteger row = 0; row < rows; row++) {
        for (NSInteger col = 0; col < cols; col++) {
            if ([self haspathCore:matrix :rows :cols :row :col :str :visited :pathLength]) {
                return YES;
            }
        }
    }
    return NO;
}

- (BOOL)haspathCore:(NSArray *)matrix :(NSInteger)rows :(NSInteger)cols :(NSInteger)row :(NSInteger)col :(NSString *)str :(bool *)visited :(NSInteger)pathLength
{
    if (str.length <= pathLength) {
        return YES;
    }
        bool haspath = false;
    
    if (row >= 0 && row < rows && col >= 0 && row < rows && [str characterAtIndex:pathLength] == [matrix[row][col] characterAtIndex:0] && !visited[row*cols + col]) {
        
        pathLength++;
        visited[row*cols+col] = true;
        
        haspath = [self haspathCore:matrix :rows :cols :row :col-1 :str :visited :pathLength]
                || [self haspathCore:matrix :rows :cols :row :col+1 :str :visited :pathLength]
                || [self haspathCore:matrix :rows :cols :row-1 :col :str :visited :pathLength]
                || [self haspathCore:matrix :rows :cols :row+1 :col :str :visited :pathLength];
        
        if (!haspath) {
            pathLength--;
            visited[row*cols+col] = false;
        }
    }
    
    return haspath;
}

#pragma mark - 14.剪绳子

//解法1
- (NSInteger)maxProductAfterCutting_solution1:(NSInteger)length
{
    if (length < 2) {
        return 0;
    }
    if (length == 2) {
        return 1;
    }
    if (length == 3) {
        return 2;
    }
    
    NSMutableArray *array = [NSMutableArray arrayWithCapacity:length + 1];
    array[0] = @0;
    array[1] = @1;
    array[2] = @2;
    array[3] = @3;
    
    NSInteger max = 0;
    
    for (NSInteger i = 4; i <= length; i++) {
        max = 0;
        
        for (NSInteger j = 1; j < i; j++) {
            if ([array[j] integerValue]*[array[i-j] integerValue] > max) {
                max = [array[j] integerValue]*[array[i-j] integerValue];
            }
        }
        array[i] = @(max);
    }
    return max;
}

//解法2
- (NSInteger)maxProductAfterCutting_solution2:(NSInteger)length
{
    if (length < 2) {
        return 0;
    }
    if (length == 2) {
        return 1;
    }
    if (length == 3) {
        return 2;
    }
    
    NSInteger numberOf3 = length / 3;
    
    if (length - 3 * numberOf3 == 1) {
        numberOf3--;
    }
    
    NSInteger numberOf2 = (length - 3*numberOf3) / 2;
    
    return (pow(3, numberOf3) * pow(2, numberOf2));
}


@end
