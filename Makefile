all: cs2123p5Driver

cs2123p5Driver: cs2123p5Driver.o cs2123p5Find_Insert_Delete.o cs2123p5Print_Free_Quoteez.o 
	gcc cs2123p5Driver.o cs2123p5Find_Insert_Delete.o cs2123p5Print_Free_Quoteez.o -o p5

cs2123p5Driver.o: cs2123p5Driver.c
	gcc -c cs2123p5Driver.c

cs2123p5Find_Insert_Delete.o: cs2123p5Find_Insert_Delete.c
	gcc -c cs2123p5Find_Insert_Delete.c

cs2123p5Print_Free_Quoteez.o: cs2123p5Print_Free_Quoteez.c
	gcc -c cs2123p5Print_Free_Quoteez.c


