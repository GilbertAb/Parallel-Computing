APPNAME=goldbach_serial
EXECUTABLES= $(APPNAME) $(APPNAME)_asan $(APPNAME)_msan

all: $(EXECUTABLES)

$(APPNAME): $(APPNAME).c
	cc -g -Wall -Wextra $(APPNAME).c goldbach_sums_array.c -o $(APPNAME) -lm

$(APPNAME)_asan: $(APPNAME).c
	cc -g -Wall -Wextra -fsanitize=address $(APPNAME).c goldbach_sums_array.c -o $(APPNAME)_asan -lm

$(APPNAME)_msan: $(APPNAME).c
	clang -g -Wall -Wextra -fsanitize=memory $(APPNAME).c goldbach_sums_array.c -o $(APPNAME)_msan -lm

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
