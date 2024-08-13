#cli.zig: c/cli.c ../include/cli.h
#	zig translate-c c/cli.c > cli.zig -I/usr/include/lua5.3 -llua5.3 -lc

le-cli: main.zig
	zig build-exe main.zig -I/usr/include/lua5.3 -llua5.3 -lc
	mv main le-cli

clean:
	rm *.o
	rm cli.zig

.PHONY: clean
