src = $(wildcard ./src/*.c)
target = $(patsubst ./src/%.c,%,$(src))
ALL:$(target)

$(target):%:./src/%.c
	gcc $< -o $@
clean:
	-rm -rf $(target)
.PHONY: clean ALL
