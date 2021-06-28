APPNAME=goldbach_pthread
EXECUTABLES= $(APPNAME) $(APPNAME)_asan $(APPNAME)_msan $(APPNAME)_tsan
CC=cc
CC2=clang
CFLAGS=-g -Wall -Wextra
LIBS=-pthread

all: $(EXECUTABLES)

$(APPNAME): $(APPNAME).c
	$(CC) $(CFLAGS) main.c $(APPNAME).c array_int64.c goldbach_sums_array.c -o $(APPNAME) $(LIBS)

$(APPNAME)_asan: $(APPNAME).c
	$(CC) $(CFLAGS) -fsanitize=address main.c $(APPNAME).c array_int64.c goldbach_sums_array.c -o $(APPNAME)_asan $(LIBS)

$(APPNAME)_msan: $(APPNAME).c
	$(CC2) $(CFLAGS) -fsanitize=memory main.c $(APPNAME).c array_int64.c goldbach_sums_array.c -o $(APPNAME)_msan $(LIBS)

$(APPNAME)_tsan: $(APPNAME).c
	$(CC2) $(CFLAGS) -fsanitize=thread main.c $(APPNAME).c array_int64.c goldbach_sums_array.c -o $(APPNAME)_tsan $(LIBS)

.PHONY: memcheck
memcheck:
	valgrind ./$(APPNAME)

.PHONY: helgrind
helgrind:
	valgrind --tool=helgrind --quiet ./$(APPNAME)

.PHONY: rebuild
rebuild: clean $(EXECUTABLES)

.PHONY: gitignore
gitignore:
	echo $(EXECUTABLES) | tr " " "\n" > .gitignore

.PHONY: lint
lint:
	cpplint --filter=-readability/casting main.c $(APPNAME).c $(APPNAME).h array_int64.c array_int64.h goldbach_sums_array.c goldbach_sums_array.h

.PHONY: clean
clean:
	rm -rf $(EXECUTABLES)
