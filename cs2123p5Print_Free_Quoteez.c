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


Parameters:


Notes:


**************************************************************************/
void printPriceMenu(Tree tree)
{
    NodeT *pNode = malloc(sizeof(NodeT));
    pNode = tree->pRoot;
    double dTotal = 0;
    printNodes(pNode, &dTotal);
    printf("Total\t\t\t\t\t\t%.2lf\n", dTotal);
    //free(pNode);
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


Parameters:


Notes:



**************************************************************************/
void printOne(Tree tree, char szId[])
{
    NodeT *pNode = malloc(sizeof(NodeT));
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


Notes:



**************************************************************************/
void freeSubTree(NodeT *p)
{
    //do nothing if passed a non-existant node
    if (p == NULL)
        return;
    //deallocates nodes
    freeSubTree(p->pSibling);
    freeSubTree(p->pChild);
    free(p);
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
    free(tree);
}
