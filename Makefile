SRC_DIR := "src"
SRC_FILES != find $(SRC_DIR) -iname "*.c" -o -iname "*.h"

main: $(SRC_FILES)
	gcc -o cpass $^

.PHONY: clean
clean:
	find . -iname "main" -o -iname "*.o" -exec rm {} \;