#target: prerrequisites
#command to build target
EXE=hello_w

all: $(EXE) $(EXE)_asan $(EXE)_msan $(EXE)_tsan

$(EXE): hello_w.c
	cc -g -Wall -Wextra hello_w.c -o $(EXE) -pthread

$(EXE)_asan: hello_w.c
	cc -g -Wall -Wextra -fsanitize=address hello_w.c -o $(EXE)_asan -pthread

$(EXE)_msan: hello_w.c
	clang -g -Wall -Wextra -fsanitize=memory hello_w.c -o $(EXE)_msan -pthread

$(EXE)_tsan: hello_w.c
	cc -g -Wall -Wextra -fsanitize=thread hello_w.c -o $(EXE)_tsan -pthread

.PHONY: memcheck
memcheck:
	valgrind ./$(EXE)

.PHONY: helgrind
helgrind:
	valgrind --tool=helgrind --quiet ./$(EXE)

.PHONY: rebuild
rebuild: clean $(EXE) $(EXE)_asan $(EXE)_msan $(EXE)_tsan

.PHONY: gitignore
gitignore:
	echo $(EXE) $(EXE)_asan $(EXE)_msan $(EXE)_tsan | tr " " "\n" > .gitignore

.PHONY: lint
lint:
	cpplint --filter=-readability/casting hello_w.c

.PHONY: clean
clean:
	rm -rf $(EXE) $(EXE)_asan $(EXE)_msan $(EXE)_tsan
	


# -fsanitize=thread -fsanitize=address
