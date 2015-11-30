#define _CRT_SECURE_NO_WARNINGS 1

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
    printf("Price Menu:\n");
    NodeT *pNode;
    pNode = tree->pRoot;
    printNodes(pNode, 0);
    printf("\n");
}
void printNodes(NodeT *pNode, int iIndent)
{
    int i;
    if(pNode==NULL)
        return;
    for (i=0; i < iIndent; i++)
    {
        printf("        ");
    }
    if (pNode->element.cNodeType == 'O')
    {
        printf("%s "
            ,pNode->element.szTitle);
        printf("(Option)\n");
    }
    if (pNode->element.cNodeType == 'V')
            printf("%-28s %10.2lf\n"
                ,pNode->element.szTitle
                ,pNode->element.dCost);
    printNodes(pNode->pChild, iIndent+1);
    printNodes(pNode->pSibling, iIndent);

}
/******************** printQuote *****************************
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
void printQuote(NodeT *pNode, NodeT *pParent)
{
    //double dTotal = 0;
    //printf("Total\t\t\t\t\t\t%.2lf\n", dTotal);

    if(pNode == NULL)
        return;

    if (pNode->element.cNodeType == 'V')
        {
            printf("%-8s\t%-26s\t%.2lf\n"
                ,pParent->element.szTitle
                ,pNode->element.szTitle
                ,pNode->element.dCost);
            //dTotal = dTotal + pNode->element.dCost;
        }
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
    pNode = tree->pRoot;
    pNode = findId(pNode, szId);
        if(pNode != NULL)
        {
            printf("Title: %-8s\nID: %-8s\nType: %c\nCostInd: %c\nCost: %.2lf\n"
                    ,pNode->element.szTitle
                    ,pNode->element.szId
                    ,pNode->element.cNodeType
                    ,pNode->element.cCostInd
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
n/a
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
/******************** freeTree ****************************
void freeTree(Tree tree)
Purpose:
Deallocate the tree memory and all of its nodes using freeSubTree to
deallocate the nodes.

Parameters:
n/a
Notes:
n/a
**************************************************************************/
void freeTree(Tree tree)
{
    //do nothing if passed a NULL tree
    if (tree == NULL)
        return;
    //deallocates all nodes
    freeSubTree(tree->pRoot);
    free (tree);
}
/******************** allocateNodeT ****************************
NodeT *allocateNodeT(Element value)
Purpose:
Create memory allocation for node to be inserted.

Parameters:
I   NodeT pNew  New node pointer to be inserted into tree

Notes:
n/a
**************************************************************************/
NodeT *allocateNodeT(Element value)
{
    NodeT *pNew = (NodeT *) malloc(sizeof(NodeT));
    pNew->element = value;
    pNew->pChild = NULL;
    pNew->pSibling = NULL;
    return pNew;
}
