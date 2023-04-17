.PHONY: all dvi clean

all:
	cmake . -B build
	cd build && make
	mv build/AnalogClock .
	./AnalogClock

dvi:
	doxygen Doxyfile
	cp -r ../images ../documentation/html

clean:
	-rm -rf ../documentation build logs AnalogClock
