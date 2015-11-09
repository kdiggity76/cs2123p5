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
    if (strcmp(szId, p->element.szId)==0) {
        return p;
    else if(strcmp(p->element.cNodeType, 'O')==0)
        findId(p->pChild, szId);
    else if(strcmp(p->element.cNodeType, 'V')==0)
        findId(p->pSibling, szId);
    else
        return NULL;
}
/******************** findParent *****************************
NodeT *findParent(NodeT *pParent, NodeT *p, NodeT *pkid)
Purpose:


Parameters:


Notes:



**************************************************************************/
NodeT *findParent(NodeT *pParent, NodeT *p, NodeT *pkid)
{
    

}
/******************** insertPriceMenu *****************************
void insertPriceMenu(Tree tree, Element element, char szParentId[])
Purpose:


Parameters:


Notes:



**************************************************************************/
void insertPriceMenu(Tree tree, Element element, char szParentId[])
{


}
/******************** deleteItem *****************************
void deleteItem(Tree tree, char szId[])
Purpose:


Parameters:


Notes:



**************************************************************************/
void deleteItem(Tree tree, char szId[])
{


}
