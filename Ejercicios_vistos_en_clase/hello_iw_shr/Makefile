#target: prerrequisites
#command to build target
APPNAME=hello_iw_shr
EXECUTABLES=$(APPNAME) $(APPNAME)_asan $(APPNAME)_msan $(APPNAME)_tsan
CC=cc
CC2=clang
CFLAGS=-g -Wall -Wextra
LIBS=-pthread


all: $(EXECUTABLES)

$(APPNAME): $(APPNAME).c
	$(CC) $(CFLAGS) $(APPNAME).c -o $(APPNAME) $(LIBS)

$(APPNAME)_asan: $(APPNAME).c
	$(CC) $(CFLAGS) -fsanitize=address $(APPNAME).c -o $(APPNAME)_asan $(LIBS)

$(APPNAME)_msan: $(APPNAME).c
	$(CC2) $(CFLAGS) -fsanitize=memory $(APPNAME).c -o $(APPNAME)_msan $(LIBS)

$(APPNAME)_tsan: $(APPNAME).c
	$(CC) $(CFLAGS) -fsanitize=thread $(APPNAME).c -o $(APPNAME)_tsan $(LIBS)

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
	cpplint --filter=-readability/casting $(APPNAME).c

.PHONY: clean
clean:
	rm -rf $(EXECUTABLES)
	


# -fsanitize=thread -fsanitize=address
