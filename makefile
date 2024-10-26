CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = main.c cd.c display.c echo.c pwd.c history.c
HEADERS = cd.h display.h echo.h pwd.h history.h
TARGET = shell

all: $(TARGET)
$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
