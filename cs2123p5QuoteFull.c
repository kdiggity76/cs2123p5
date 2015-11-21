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
    QuoteResult *newQuote;
    NodeT *kid, 
    NodeT *kkid;
    int i,k;
    double total = 0;
      for (i = 0; i < quoteSelection->iQuoteItemCnt; i++)
      {
        kid = findId(tree->pRoot, quoteSelection->quoteItemM[i].szOptionId);
        kkid = kid->pChild;
          for (k = 1; k <= quoteSelection->quoteItemM[i].iSelection; k++)
          {
            if (kkid != NULL)
            {
              //newQuote->error = quoteSelection->quoteItemM[i];
              break;
            }
            else
              kkid = kkid->pSibling;
          }
          printf("%-7s %\n",
          kid->element.szTitle);
      }
}
