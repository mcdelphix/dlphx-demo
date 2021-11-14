CC=gcc
OBJ=menu.o

%.o: %.c
  $(CC) -c -o $@
  
menu.exe: $(OBJ)
  $CC -o $@ $^
