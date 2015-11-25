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

    for(q = 0; q < quoteSelection->iQuoteItemCnt; q++)
    {
        /*
            * This is a complete quote
            *
            QUOTE BEGIN
            QUOTE OPTION 0 model 1
            QUOTE OPTION 1 engine_base 1
            QUOTE OPTION 1 color_base 2
            QUOTE OPTION 1 audio_base 2
            QUOTE OPTION 0 warranty 2
            QUOTE END
            *
            *
            ********************************* PARTIAL QUOTE ********
            *
            QUOTE BEGIN
            QUOTE OPTION 0 model 3
            QUOTE OPTION 1 engine_oy 2
            QUOTE OPTION 1 color_oy 2
            QUOTE OPTION 0 warranty 3
            QUOTE END
            *
        */
        //using findId to find parent node szOptionId
        pKid = findId(tree->pRoot,quoteSelection->quoteItemM[q].szOptionId);
        //Print title of the Parent Node
        printf("\n%s\t", pKid->element.szTitle);
        //move to options below parent node for iSelection
        pKid = pKid->pChild;
        //traverse siblings based on iSelection, starting at 1
        for(i = 1; i < quoteSelection->quoteItemM[q].iSelection; i++){
            pKid = pKid->pSibling;
            if(pKid == NULL){
                newQuote.returnCode = QUOTE_BAD_SELECTION;
                return newQuote;
            }

        }


        printf("\t%s", pKid->element.szTitle);
        printf("\t\t\t%.2lf\n",  pKid->element.dCost);
        newQuote.dTotalCost += pKid->element.dCost;

    }
    if(quoteSelection->iQuoteItemCnt < 5)
        newQuote.returnCode = QUOTE_PARTIAL;
    else
         newQuote.returnCode = QUOTE_NORMAL;
      return newQuote;
}
