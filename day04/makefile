src = $(wildcard ./src/*.c)
target = $(patsubst ./src/%.c,%,$(src))
ALL:$(target)

$(target):%:./src/%.c
	gcc -g -O0 $< -Wall -o  $@
clean:
	-rm -rf $(target)
.PHONY: clean ALL
