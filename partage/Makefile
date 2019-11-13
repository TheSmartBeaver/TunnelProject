SRC_DIR=src/
EXEC_DIR=executable/
HEAD_DIR=headers/
TEMP_DIR=temp/

in_test: $(HEAD_DIR)extremite.h $(HEAD_DIR)tunalloc.h $(HEAD_DIR)iftun.h tunalloc.o extremite.o in_test.o iftun.o
	gcc -Iheaders -o $(EXEC_DIR)in_test $(TEMP_DIR)in_test.o $(TEMP_DIR)extremite.o $(TEMP_DIR)tunalloc.o $(TEMP_DIR)iftun.o

out_test: out_test.o extremite.o tunalloc.o iftun.o
	gcc -Iheaders -o $(EXEC_DIR)out_test $(TEMP_DIR)out_test.o $(TEMP_DIR)extremite.o $(TEMP_DIR)tunalloc.o $(TEMP_DIR)iftun.o


out_test.o: $(SRC_DIR)out_test.c
	gcc -Iheaders -o $(TEMP_DIR)out_test.o -c $(SRC_DIR)out_test.c

in_test.o: $(SRC_DIR)in_test.c
	gcc -Iheaders -o $(TEMP_DIR)in_test.o -c $(SRC_DIR)in_test.c

tunalloc.o: $(SRC_DIR)tunalloc.c
	gcc -Iheaders -o $(TEMP_DIR)tunalloc.o -c $(SRC_DIR)tunalloc.c

extremite.o: $(SRC_DIR)extremite.c
	gcc -Iheaders -o $(TEMP_DIR)extremite.o -c $(SRC_DIR)extremite.c 
iftun.o: $(SRC_DIR)iftun.c
	gcc -Iheaders -o $(TEMP_DIR)iftun.o -c $(SRC_DIR)iftun.c

rmTemp:
	rm $(TEMP_DIR)out_test.o $(TEMP_DIR)in_test.o $(TEMP_DIR)tunalloc.o 
	rm $(TEMP_DIR)extremite.o $(TEMP_DIR)iftun.o
