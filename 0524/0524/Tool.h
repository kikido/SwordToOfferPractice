//
//  Tool.h
//  0524
//
//  Created by dqh on 2018/5/24.
//  Copyright © 2018年 dqh. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, kk){
    kkOne,
    kkTwo = 5,
    kkThree
};

struct Oc_BinaryTreeNode
{
    NSInteger m_value;
    Oc_BinaryTreeNode* m_pLeft;
    Oc_BinaryTreeNode* m_pRight;
    Oc_BinaryTreeNode* m_pParent;
};

@interface Tool : NSObject

- (BOOL)duplicate:(NSMutableArray *)array duplicateNumber:(NSInteger *)duplicate;

- (NSInteger)getDuplicate:(NSMutableArray *)array;

- (BOOL)findFromArray:(NSArray *)array number:(NSInteger)number;

- (Oc_BinaryTreeNode *)construct:(NSArray *)preorder inorder:(NSArray *)inorder;

- (NSInteger)getMin:(NSArray *)array;

- (BOOL)haspath:(NSArray *)matrix str:(NSString *)str;

- (NSInteger)maxProductAfterCutting_solution1:(NSInteger)length;

- (NSInteger)maxProductAfterCutting_solution2:(NSInteger)length;
@end
