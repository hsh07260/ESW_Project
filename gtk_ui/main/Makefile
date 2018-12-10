TARGET=test_gtk
OBJECT=main.o
FLAG1=`pkg-config --cflags gtk+-3.0`
FLAG2=`pkg-config --libs gtk+-3.0`
LIB=/home/dongho/ESW/team_project/ESW_Project/gtk_ui/lib
INC=/home/dongho/ESW/team_project/ESW_Project/gtk_ui/include


$(TARGET): main.o $(LIB)/libtotal.a
	gcc $(FLAG1) -o $(TARGET) $(OBJECT) $(FLAG2) -lmysqlclient -L$(LIB) -I$(INC) -ltotal

main.o: test_gtk.c
	gcc $(FLAG1) -c -I$(INC) -o main.o $(FLAG2) test_gtk.c

clean:
	rm test_gtk main.o
