TARGET=test_gtk
OBJECT=test_gtk.c
PKG_GTK=`pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`

$(TARGET): $(OBJECT)
	gcc `pkg-config --cflags gtk+-3.0` -o $(TARGET) $(OBJECT) `pkg-config --libs gtk+-3.0`

