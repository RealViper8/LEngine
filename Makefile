./build/el: src/ include/
	cmake --build build
	./build/el

clean:
	@rm *.o
	@rm *.out

.PHONY: clean
