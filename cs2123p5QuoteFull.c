#define _CRT_SECURE_NO_WARNINGS 1
#define NULL -1

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

/******************** QuoteResult *****************************
QuoteResult determineQuote(Tree tree, QuoteSelection quoteSelection)
Purpose:


Parameters:


Notes:



**************************************************************************/
QuoteResult determineQuote(Tree tree, QuoteSelection quoteSelection)
{
    QuoteResult newQuote;
    newQuote.dTotalCost = 0.0;

    NodeT *pKid;
    int q, i;
    //i count is the iLevel, q is the count of the queue
    //check for any "notFound"'s
    for(i = 0; i < sizeof(quoteSelection->quoteItemM[i]); i++)
    {
        if (quoteSelection->quoteItemM[i].dCost == -999999)
        {
            strcpy(newQuote.error.szOptionId, quoteSelection->quoteItemM[i].szOptionId);
            newQuote.returnCode = 2;
            return newQuote;
        }
    }
    for(q = 0; q < quoteSelection->iQuoteItemCnt; q++)
    {

        //using findId to find parent node szOptionId
        pKid = findId(tree->pRoot,quoteSelection->quoteItemM[q].szOptionId);
        //move to options below parent node for iSelection
        pKid = pKid->pChild;
        //traverse siblings based on iSelection, starting at 1
        for(i = 1; i < quoteSelection->quoteItemM[q].iSelection; i++)
        {
            if (pKid->pSibling == NULL)
            {
                strcpy(newQuote.error.szOptionId, quoteSelection->quoteItemM[i].szOptionId);
                newQuote.error.iSelection = quoteSelection->quoteItemM[q].iSelection;
                newQuote.returnCode = 3;
                return newQuote;
            }
            pKid = pKid->pSibling;
        }

    }
    for(q = 0; q < quoteSelection->iQuoteItemCnt; q++)
    {

        //using findId to find parent node szOptionId
        pKid = findId(tree->pRoot,quoteSelection->quoteItemM[q].szOptionId);
        //Print title of the Parent Node
        printf("\n%s\t", pKid->element.szTitle);
        //move to options below parent node for iSelection
        pKid = pKid->pChild;
        //traverse siblings based on iSelection, starting at 1
        for(i = 1; i < quoteSelection->quoteItemM[q].iSelection; i++)
        {
            //not needed since error check already performed
            /*
            if (pKid->pSibling == NULL)
            {
                newQuote.returnCode = 3;
                return newQuote;
            }
            */
            pKid = pKid->pSibling;
        }

        printf("\t%s", pKid->element.szTitle);
        printf("\t\t\t%.2lf\n",  pKid->element.dCost);
        newQuote.dTotalCost += pKid->element.dCost;

    }
    if(quoteSelection->iQuoteItemCnt < 5)
        newQuote.returnCode = 1;
    else
         newQuote.returnCode = 0;
      return newQuote;
}
