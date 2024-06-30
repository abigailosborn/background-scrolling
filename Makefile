S = src/
I = include/
B = build/
OBJ_FILES = $(B)background
FLAGS = -I$(I) -Iraylib-5.0_linux_amd64/include -Lraylib-5.0_linux_amd64/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

$(B)background:
	gcc $(B)background.c $(FLAGS) -o $@

clean:
	rm -rf build

