#target: prerrequisites
#command to build target

all: hello hello_asan hello_msan hello_tsan

hello: main.c
	cc -g -Wall -Wextra main.c -o hello -pthread

hello_asan: main.c
	cc -g -Wall -Wextra -fsanitize=address main.c -o hello_asan -pthread

hello_msan: main.c
	clang -g -Wall -Wextra -fsanitize=memory main.c -o hello_msan -pthread

hello_tsan: main.c
	cc -g -Wall -Wextra -fsanitize=thread main.c -o hello_tsan -pthread

.PHONY: memcheck
memcheck:
	valgrind ./hello

.PHONY: helgrind
helgrind:
	valgrind --tool=helgrind --quiet ./hello

.PHONY: rebuild
rebuild: clean hello hello_asan hello_msan hello_tsan

.PHONY: gitignore
gitignore:
	echo hello hello_asan hello_msan hello_tsan | tr " " "\n" > .gitignore

.PHONY: lint
lint:
	cpplint --filter=-readability/casting main.c

.PHONY: clean
clean:
	rm -rf hello hello_asan hello_msan hello_tsan
	


# -fsanitize=thread -fsanitize=address
