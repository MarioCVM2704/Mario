CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I"C:/OpenSSL-Win64/include"
LDFLAGS = -L"C:\OpenSSL-Win64\lib\VC\x64\MDd" -lssl -lcrypto

SRC = main.c utils.c gestion.c auth.c
OBJ = $(SRC:.c=.o)
EXEC = programme.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del *.o *.exe
