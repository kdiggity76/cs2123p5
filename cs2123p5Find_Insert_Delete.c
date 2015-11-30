#define _CRT_SECURE_NO_WARNINGS 1
#define NULL -1

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

/******************** findId *****************************
NodeT *findId(NodeT *p, char szId[])
 
Purpose: This function will find the node of the Id that is passed in through its parameters
 and returns the address of the node. Will return NULL if Id is not found.

Parameters: 
    NodeT *p: The current/beginning node being passed to start searching
 
    char szId[]: The Id passed in in order to find the its node.


Notes:



**************************************************************************/
NodeT *findId(NodeT *p, char szId[])
{
    if (p == NULL)
        return;
    if (strcmp(p->element.szId, szId) == 0)
        return p;
    if (findId(p->pChild, szId) == NULL)
        return findId(p->pSibling, szId);
    else
        return findId(p->pChild, szId);
}
/******************** findParent *****************************
 NodeT *findParent(NodeT *pParent, NodeT *p, NodeT *pkid)
 
 Purpose: Finds the logical parent node of the child node passed in as pkid.
 Will return the address of the parent node or return NULL if not found.


 Parameters:
    NodeT *pParent: The parent node being passed in in order to mark the parent location. it is initially NULL.
 
    NodeT *p: The Node passed in to start searching recursively.
 
    NodeT *pkid: The Node that will be used to find the parent.


 Notes:



 **************************************************************************/
NodeT *findParent(NodeT *pParent, NodeT *p, NodeT *pkid)
{

    if (p==NULL)
        return NULL;
    if (pkid == NULL)
        return NULL;

    if (p == pkid)
        return pParent;
    if (findParent(p, p->pChild, pkid) == NULL)
        return findParent(pParent, p->pSibling, pkid);
    else
        return findParent(p, p->pChild, pkid);
}
/******************** insertPriceMenu *****************************
 void insertPriceMenu(Tree tree, Element element, char szParentId[])
 
 Purpose: This function will insert the node into the tree that is passed in the parameters.
 This function also contains a seperate function that helps in the insertion process.


 Parameters:
    Tree tree: The entire tree passed in to start searching/inserting from Root
 
    Element element: The element structure that contains all the info of
            the node that needs to be inserted.
 
    char szParentId[]: The Id of the parent to find where the Node should be inserted


 Notes:



 **************************************************************************/
void insertPriceMenu(Tree tree, Element element, char szParentId[])
{
    NodeT *pkid;
    NodeT *pParent;

    pkid = findId(tree->pRoot, element.szId);
    if (pkid != NULL)
    {
        printf("\tWarning: Id Already in Tree\n");
        return;
    }
    if (strcmp(szParentId, "ROOT") ==0)
        insertIntoSibling(&(tree->pRoot), element);
    else
    {
        pParent = findId(tree->pRoot, szParentId);
        if (pParent->element.cNodeType == element.cNodeType)
        {
            printf("Define ERROR: Value cannot be linked to another value.\n");
            return;
        }
        if (pParent == NULL)
        {
            printf("\tParent Not Found\n");
            return;
        }
        insertIntoSibling(&(pParent->pChild), element);
    }
}

/******************** insertIntoSibling *****************************
 void insertIntoSibling(NodeT **pp, Element element)
 
 Purpose: This function is used in insertPriceMenu and it allocates space
        and inserts the new node into the tree.


 Parameters:
    NodeT **pp: The address of the node that needs to be inserted.
 
    Element element: The element structure of the data that will be
            inserted into the node space.

 Notes:



 **************************************************************************/
void insertIntoSibling(NodeT **pp, Element element)
{
    if(*pp == NULL)
        *pp = allocateNodeT(element);
    else
        insertIntoSibling(&((*pp)->pSibling), element);
}
/******************** *beforeSibling *****************************
 NodeT *beforeSibling(NodeT *p, NodeT *pKid)
 
 Purpose: This function works with the delete function to find the node before the 
        node that needs to be found.
 
 
 Parameters:
 
    NodeT *p: The Node passed in to start searching recursively.
 
    NodeT *pkid: The Node that will be used to find the parent.
 
 Notes:
 
 
 
 **************************************************************************/
NodeT *beforeSibling(NodeT *p, NodeT *pKid)
{
    if (p ==NULL)
        return;
    if (p->pSibling != pKid)
        return beforeSibling(p->pSibling, pKid);
    else
        return p;
}
/******************** deleteItem *****************************
 void deleteItem(Tree tree, char szId[])
 
 Purpose: This function will delete the node that is passed in through the parameter
        and will keep the previous and upcoming nodes connected to each other.


 Parameters:
    Tree tree: The entire tree passed in to start searching/inserting from Root
    
    char szId[]: The Id passed in in order to find the its node.
 Notes:



 **************************************************************************/
void deleteItem(Tree tree, char szId[])
{
    NodeT *pkid;
    NodeT *pParent;
    NodeT *pTemp;

    pkid = findId(tree->pRoot, szId);
    pParent = findParent(pParent, tree->pRoot, pkid);
    if (pParent->pChild == pkid)
    {
        pParent->pChild = pkid->pSibling;
        pkid->pSibling = NULL;
    }
    else
    {
        pTemp = beforeSibling(pParent->pChild, pkid);
        pTemp->pSibling = pkid->pSibling;
        pkid->pSibling = NULL;
    }
    freeSubTree(pkid);
    printf("*\n****************************** DELETE ***************\n*\n");
    printf("DELETE %s\n", szId);

}
