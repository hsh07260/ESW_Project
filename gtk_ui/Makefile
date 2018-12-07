TARGET=test_gtk
OBJECT=test_gtk.c
PKG_GTK=`pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`



$(TARGET): $(OBJECT) #libinsert_data.a
	gcc `pkg-config --cflags gtk+-3.0` -o $(TARGET) $(OBJECT) `pkg-config --libs gtk+-3.0` -lmysqlclient #-L. -linsert_data


libinsert_data.a: insert_data.o
	ar rv libinsert_data.a insert_data.o

insert_data.o: insert_data.c
	gcc -c insert_data.c


clean:
	rm test_gtk insert_data.o libinsert_data.a
