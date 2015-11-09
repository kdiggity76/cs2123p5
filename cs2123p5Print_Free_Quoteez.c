#define _CRT_SECURE_NO_WARNINGS 1
#define NULL -1

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

/******************** createTree *****************************
Tree createTree()
Purpose:


Parameters:


Notes:


**************************************************************************/
Tree testTree()
{
 Tree tree = (Tree)malloc(sizeof(TreeImp));
    if (tree == NULL)
        ErrExit(ERR_ALGORITHM, "malloc allocation error for TreeImp");
    tree-&gt;
    tree.pRoot.element.szTitle = "Model";
    tree.pRoot.pChild.element.szTitle = "Engine";
    tree.pRoot.
    tree.pRoot.pSibling.element = "Warrenty";
    return tree;

}
/******************** printPriceMenu *****************************
void printPriceMenu(Tree tree)
Purpose:


Parameters:


Notes:


**************************************************************************/
void printPriceMenu(Tree tree)
{


}
/******************** printOne *****************************
void printOne(Tree tree, char szId[])
Purpose:


Parameters:


Notes:



**************************************************************************/
void printOne(Tree tree, char szId[])
{


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
    freeSubTree(p->pChild);
    freeSubTree(p->pSibling);
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
