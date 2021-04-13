#target: prerrequisites
#command to build target
all: hello hello_asan hello_msan hello_tsan

hello: main.c
	cc -g -Wall -Wextra main.c -o hello -pthread

hello_asan: main.c
	cc -g -Wall -Wextra -fsanitize=address main.c -o hello_asan -pthread

hello_msan: main.c
#	cc -g -Wall -Wextra -fsanitize=memory main.c -o hello_msan -pthread

hello_tsan: main.c
	cc -g -Wall -Wextra -fsanitize=thread main.c -o hello_tsan -pthread

.PHONY: rebuild
rebuild: clean hello hello_asan hello_msan hello_tsan

.PHONY: gitignore
gitignore:
	echo hello hello_asan hello_msan hello_tsan | tr " " "\n" > .gitignore

.PHONY: clean
clean:
	rm -rf hello hello_asan hello_msan hello_tsan

# -fsanitize=thread -fsanitize=address
