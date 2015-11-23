all: cs2123p5Driver

cs2123p5Driver: cs2123p5Driver.o cs2123p5Find_Insert_Delete.o cs2123p5Print_Free_Quoteez.o cs2123p5QuoteFull.o
	gcc cs2123p5Driver.o cs2123p5Find_Insert_Delete.o cs2123p5Print_Free_Quoteez.o cs2123p5QuoteFull.o -g -o p5

cs2123p5Driver.o: cs2123p5Driver.c
	gcc -g -c cs2123p5Driver.c

cs2123p5Find_Insert_Delete.o: cs2123p5Find_Insert_Delete.c
	gcc -g -c cs2123p5Find_Insert_Delete.c

cs2123p5Print_Free_Quoteez.o: cs2123p5Print_Free_Quoteez.c
	gcc -g -c cs2123p5Print_Free_Quoteez.c

cs2123p5Print_Free_Quoteez.o: cs2123p5Print_Free_Quoteez.c
	gcc -g -c cs2123p5QuoteFull.c

