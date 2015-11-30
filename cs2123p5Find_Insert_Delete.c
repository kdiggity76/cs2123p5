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
        return p;
    if (strcmp(p->element.szId, szId) == 0)
        return p;
    if (findId(p->pChild, szId) == NULL)
        return findId(p->pSibling, szId);
    else
        return findId(p->pChild, szId);
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
//Logan's version

NodeT *beforeSibling(NodeT *p, NodeT *pKid)
{
    if (p ==NULL)
        return p;
    if (p->pSibling != pKid)
        return beforeSibling(p->pSibling, pKid);
    else
        return p;
}

/******************** findParent *****************************
 NodeT *findParent(NodeT *pParent, NodeT *p, NodeT *pkid)
 Purpose:


 Parameters:


 Notes:



 **************************************************************************/
NodeT *findParent(NodeT *pParent, NodeT *p, NodeT *pKid)
{
    //p set to first child of parent node
    p = pParent->pChild;
    if(p != NULL)
        printf("p is now child %s of pParent %s\n", p->element.szId, pParent->element.szId);

    if(p == NULL){
        //no child nodes left
        printf("p was NULL");
        return p;
    }
    else if(strcmp(p->element.szId, pKid->element.szId) == 0)
        //if match, pParent should be the Parent ID
        return pParent;
    else
    {
            //Parent node is now p to search through p's child nodes
            pParent = p;
            pParent = findParent(pParent, p, pKid);
    }

    pParent = pParent->pSibling;
    pParent = findParent(pParent, p, pKid);

    return pParent;
}

/******************** deleteItem *****************************
 void deleteItem(Tree tree, char szId[])
 Purpose:


 Parameters:


 Notes:

 n

 **************************************************************************/
    void deleteItem(Tree tree, char szId[])
{
    NodeT *pKid;
    NodeT *pParent;
    NodeT *pTemp = NULL;


    //find Node
    //delete all Node's children
    //connect Node's sibling's (or sibling to parent if Node is connected to parent)
    //free Node

    pKid = findId(tree->pRoot, szId);
    pParent = findParent(tree->pRoot, pTemp, pKid);
    pTemp = beforeSibling(pParent->pChild, pKid);

    pTemp->pSibling = pKid->pSibling;
    pKid->pSibling = NULL;
    freeSubTree(pKid);

}
