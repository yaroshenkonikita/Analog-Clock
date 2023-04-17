.PHONY: all dvi clean

all:
	cmake . -B build
	cd build && make
	./build/AnalogClock

dvi:
	doxygen Doxyfile

clean:
	-rm -rf ../documentation build logs AnalogClock
