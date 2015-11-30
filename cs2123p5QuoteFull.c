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

    int q, i, k;
    //i count is the iLevel, q is the count of the queue
    //check for any "notFound"'s
    for(i = 0; i < quoteSelection->iQuoteItemCnt; i++)
    {

        if (quoteSelection->quoteItemM[i].dCost == -999999)
        {
            strcpy(newQuote.error.szOptionId, quoteSelection->quoteItemM[i].szOptionId);
            newQuote.returnCode = 2;
            return newQuote;
        }

        for(k = 0; k < quoteSelection->iQuoteItemCnt; k++)
        {

            if(k == i)
                continue;
            else if(quoteSelection->quoteItemM[k].iLevel == quoteSelection->quoteItemM[i].iLevel)
            {
                if(strcmp(quoteSelection->quoteItemM[k].szOptionId, quoteSelection->quoteItemM[i].szOptionId) == 0)
                {
                    newQuote.returnCode = 2;
                    return newQuote;
                }

            }
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
    if (quoteSelection->iQuoteItemCnt < 5)
        printf("*\n************************* PARTIAL QUOTE **************\n*\n");
    else
        printf("*\n************************* QUOTE **********************\n*\n");
    for(q = 0; q < quoteSelection->iQuoteItemCnt; q++)
    {

        //using findId to find parent node szOptionId
        pKid = findId(tree->pRoot,quoteSelection->quoteItemM[q].szOptionId);
        //Print title of the Parent Node
        printf("%-10s   ", pKid->element.szTitle);
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

        printf("  %-28s", pKid->element.szTitle);
        printf("  %.2lf\n",  pKid->element.dCost);
        newQuote.dTotalCost += pKid->element.dCost;

    }
    if(quoteSelection->iQuoteItemCnt < 5)
        newQuote.returnCode = 1;
    else
         newQuote.returnCode = 0;
      return newQuote;
}
