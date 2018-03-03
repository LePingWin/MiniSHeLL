/*
�* File:��  StackTree.h
�* Author:  zentut.com
�* Purpose: linked StackTree header file
�*/
#ifndef _STACK_TREE_H_
#define _STACK_TREE_H_

#include "../include/typedef.h"


StackTree newNodeStackTree(Tree data);

bool isEmptyStackTree(StackTree root);
 
void pushStackTree(StackTree* root, Tree data);

Tree popStackTree(StackTree* root);

Tree peekStackTree(StackTree root);
#endif // LINKEDStackTree_H_INCLUDED