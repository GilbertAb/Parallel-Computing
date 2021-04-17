APPNAME=goldbach_serial
EXECUTABLES= $(APPNAME) $(APPNAME)_asan $(APPNAME)_msan $(APPNAME)_tsan

all: $(EXECUTABLES)

$(APPNAME): $(APPNAME).c
	cc -g -Wall -Wextra $(APPNAME).c -o $(APPNAME)

$(APPNAME)_asan: $(APPNAME).c
	cc -g -Wall -Wextra -fsanitize=address $(APPNAME).c -o $(APPNAME)_asan

$(APPNAME)_msan: $(APPNAME).c
	clang -g -Wall -Wextra -fsanitize=memory $(APPNAME).c -o $(APPNAME)_msan

$(APPNAME)_tsan: $(APPNAME).c
	cc -g -Wall -Wextra -fsanitize=thread $(APPNAME).c -o $(APPNAME)_tsan
	
#$(APPNAME)_ubsan: $(APPNAME).c
#	clang -g -Wall -Wextra -fsanitize=undefined $(APPNAME).c -o $(APPNAME)_ubsan

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
