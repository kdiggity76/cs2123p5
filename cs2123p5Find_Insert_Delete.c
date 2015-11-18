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
        return NULL;
    if (strcmp(szId, p->element.szId)==0)
        return p;
    return findId(p->pChild, szId);
    return findId(p->pSibling, szId);
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
    NodeT *pNode;
    NodeT *pParent;
    pNode = allocateNodeT(element);
    if(tree->pRoot == NULL)
    {
        tree->pRoot = pNode;
        return;
    }
    if(strcmp(szParentId, "ROOT")==0)
    {
    pParent = tree->pRoot;
    insertChild(pNode, pParent->pSibling);
    }
    else
    {
    pParent = findId(tree->pRoot, szParentId);
    insertChild(pNode, pParent->pChild);
    }
}
void insertChild(NodeT *pNode, NodeT *tempNode)
{
     if(tempNode == NULL)
     {
     tempNode = pNode;
        return;
     }
    if (tempNode->pSibling == NULL)
    {
        tempNode->pSibling = pNode;
        return;
    }
    else insertChild(pNode, tempNode->pSibling);
}
/******************** deleteItem ****************************
void deleteItem(Tree tree, char szId[])
Purpose:


Parameters:


Notes:



**************************************************************************/
void deleteItem(Tree tree, char szId[])
{


}
