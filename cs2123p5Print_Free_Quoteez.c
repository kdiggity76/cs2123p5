#define _CRT_SECURE_NO_WARNINGS 1
#define NULL -1

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"


/******************** printPriceMenu *****************************
void printPriceMenu(Tree tree)
Purpose:
Print the entire tree in order format. Assigns the first node in the
tree and then send to a recursive functions. Recusive function traverses
the tree and prints all the Option nodes and thier corrisponding Option nodes.

Parameters:
I   NodeT pNode     Placeholder pointer for the root node
I   double dTotal   Tracks total cost of the order

Notes:
If empty tree is passed to the function it will do nothing.

**************************************************************************/
void printPriceMenu(Tree tree)
{
    NodeT *pNode;
    pNode = tree->pRoot;
    double dTotal = 0;
    printNodes(pNode, &dTotal);
    printf("Total\t\t\t\t\t\t%.2lf\n", dTotal);
}
void printNodes(NodeT *pNode, double *dTotal)
{
    if(pNode==NULL)
        return;
    if (pNode->element.cNodeType == 'O')
        {
            printf("%-8s\t%-26s\t%.2lf\n"
                ,pNode->element.szTitle
                ,pNode->pChild->element.szTitle
                ,pNode->pChild->element.dCost);
            *dTotal = *dTotal + pNode->pChild->element.dCost;
        }
    printNodes(pNode->pChild, dTotal);
    printNodes(pNode->pSibling, dTotal);
}
/******************** printOne *****************************
void printOne(Tree tree, char szId[])
Purpose:
Prints one item from the tree.
This is used from the PRINT ONE command.

Parameters:
I   NodeT pNode     Assigned as pointer node to the result if the findID function
I   char szID       Passed value used to find desired node in tree

Notes:
If node is not found the function will print nothing.

**************************************************************************/
void printOne(Tree tree, char szId[])
{
    NodeT *pNode;
    //pNode = findId(tree->pRoot, szId);
        if(pNode != NULL)
        {
            printf("%-8s\t%-26s\t%.2lf\n"
                    ,pNode->element.szTitle
                    ,pNode->element.szTitle
                    ,pNode->element.dCost);
        }
}
/******************** freeSubTree *****************************
void freeSubTree(NodeT *p)
Purpose:
Deallocates the memory for the node and all of its subnodes.

Parameters:
I   NodeT p     Starting node to be freed

Notes:



**************************************************************************/
void freeSubTree(NodeT *p)
{
    //do nothing if passed a non-existant node
    if (p == NULL)
        return;
    //free child and sibling nodes starting from passed node
    freeSubTree(p->pSibling);
    freeSubTree(p->pChild);
    free (p);
}
/******************** freeTree *****************************
void freeTree(Tree tree)
Purpose:
Deallocate the tree memory and all of its nodes using freeSubTree to
deallocate the nodes.

Parameters:


Notes:



**************************************************************************/
void freeTree(Tree tree)
{
    //do nothing if passed a non-existant tree
    if (tree == NULL)
        return;
    //deallocates all nodes
    freeSubTree(tree->pRoot);
    free (tree);
}
