
.PHONY: make

make:
	echo "To use: make <tesname>"
	echo "Example: make test"

%: %.c
	gcc -I"/usr/include/SDL2" -L../out/ -Wall $< -o $@.out -lSDL_Clicky -lSDL2



