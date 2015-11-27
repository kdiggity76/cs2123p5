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
    else
    {
        return findParent(p, p->pChild, pkid);
        return findParent(pParent, p->pSibling, pkid);
    }
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
        if (pParent == NULL)
        {
            printf("\tParent Not Found\n");
            return;
            //ErrExit(ERR_ALGORITHM, "Parent Not Found",...);
        }
        insertIntoSibling(&(pParent->pChild), element);
    }
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
    NodeT *pBeforeSibling;

    pkid = findId(tree->pRoot, szId);
    pParent = findParent(pParent, tree->pRoot, pkid);

    pBeforeSibling = beforeSibling(&(pParent->pChild), pkid);
    pBeforeSibling->pSibling = pkid->pSibling;
    pkid->pSibling = NULL;
    freeSubTree(pkid);

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







