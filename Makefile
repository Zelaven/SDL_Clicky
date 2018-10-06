
# Compiler to use. Make does something special with this.
CC = gcc
CFLAGS = -I"/usr/include/SDL2" -g -Wall -lSDL2

ODIR = obj
SDIR = src

_DEPS = SDL_Clicky.h clickable.h containers/containers.h
DEPS = $(patsubst %,$(SDIR)/%,$(_DEPS))
_SRC = SDL_Clicky.c clickable.c
SRC = $(patsubst %,$(SDIR)/%,$(_SRC))
_OBJS = $(_SRC:.c=.o)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))
OUT = out/libSDL_Clicky.a

# Rules that are always executed regardless of file states.
.POHNY: clean force forceobjs

# Name isn't special, it's just befitting of being the first rule. The first rule is executed if no rule is specified.
make: $(OUT)
#	echo $(OBJS) #Uncomment this line to see if the target gets run or just to get a list of the objs or whatever.

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

#obj/SDL_Clicky.o: src/SDL_Clicky.c $(DEPS)
#	$(CC) -c $< -o $@

#obj/%.o: src/%.c $(DEPS)
#	$(CC) -c $< -o $@

# Compiling the actual build.
$(OUT): $(OBJS)
	#$(CC) $(OBJS) -c -o obj/libSDL_Clicky.o;
	#ar rcs $(OUT) obj/libSDL_Clicky.o;
	ar rcs $(OUT) $(OBJS);

# Primitive targets for forcing a compilation. Cleans up after themselves. NOT UPDATED FOR USE HERE! IT WAS COPY-PASTED FROM ELSEWHERE!
forceobjs:
	$(CC) -c $(SRC)

force: forceobjs
	$(CC) $(_OBJS) -o $(OUT); rm *.o

# Rule that is always executed regardless of the states of the files. Deletes junk.
clean:
	rm $(OUT) $(ODIR)/*.o;

asdf:
	echo $(OBJS)

