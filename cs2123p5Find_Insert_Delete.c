#define _CRT_SECURE_NO_WARNINGS 1
#define NULL -1

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

/******************** findId *****************************
NodeT *findId(NodeT *p, char szId[])
Purpose:


Parameters:


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
 Purpose:


 Parameters:


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
 Purpose:


 Parameters:


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
 Purpose:


 Parameters:


 Notes:



 **************************************************************************/
void insertIntoSibling(NodeT **pp, Element element)
{
    if(*pp == NULL)
        *pp = allocateNodeT(element);
    else
        insertIntoSibling(&((*pp)->pSibling), element);
}

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
 Purpose:


 Parameters:


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

}
