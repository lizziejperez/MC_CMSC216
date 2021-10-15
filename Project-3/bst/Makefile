TARGET=test_driver
OBJS=bst.o
CC=gcc
CFLAGS=-Wall -pedantic-errors -Werror -std=c99

$(TARGET):driver.c $(OBJS)
        $(CC) $(CFLAGS) driver.c $(OBJS) -o $(TARGET)

clean:
        rm -rf $(OBJS) $(TARGET)