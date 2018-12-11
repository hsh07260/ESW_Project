INC=/home/dongho/ESW/team_project/ESW_Project/gtk_ui/include
FLAG1=`pkg-config --cflags gtk+-3.0`
FLAG2=`pkg-config --libs gtk+-3.0`

libtotal.a: insert_data.o remove_data.o myinput.o init_list.o init_set.o
	ar rv libtotal.a insert_data.o remove_data.o myinput.o init_list.o init_set.o

insert_data.o: insert_data.c $(INC)/insert_data.h
	gcc -c insert_data.c -I$(INC) -lmysqlclient -o insert_data.o

remove_data.o: remove_data.c $(INC)/remove_data.h
	gcc -c remove_data.c -I$(INC) -lmysqlclient -o remove_data.o

myinput.o: myinput.c $(INC)/insert_data.h
	gcc $(FLAG1) -c myinput.c -I$(INC) -o myinput.o $(FLAG2)

init_list.o: init_list.c $(INC)/myinit.h
	gcc $(FLAG1) -c init_list.c -I$(INC)/ -o init_list.o $(FLAG2)

init_set.o: init_set.c $(INC)/myinit.h
	gcc $(FLAG1) -c init_set.c -I$(INC)/ -o init_set.o $(FLAG2)

clean:
	rm libtotal.a insert_data.o myinput.o init_list.o init_set.o remove_data.o
