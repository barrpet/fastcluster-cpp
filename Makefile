INSTALL_PREFIX=/usr/local

default: all

all: libfastcluster.a

libfastcluster.a: ./src/fastcluster.o
	ar -rc $@ $<
	ranlib $@

src/fastcluster.o: ./src/Makefile
	cd src && $(MAKE)

run_tests: ./test/build/unit_tests
	./test/build/unit_tests $(MARGS)

test: ./test/build/unit_tests
./test/build/unit_tests: ./test/build
	cd ./test/build && cmake .. && $(MAKE) unit_tests

./test/build:
	mkdir ./test/build

install: libfastcluster.a include/fastcluster.h
	cp libfastcluster.a $(INSTALL_PREFIX)/lib/
	cp include/fastcluster.h $(INSTALL_PREFIX)/include/

uninstall:
	rm -fv $(INSTALL_PREFIX)/lib/libfastcluster.a $(INSTALL_PREFIX)/include/fastcluster.h

clean:
	cd src && $(MAKE) clean

purge: clean
	rm -fr libfastcluster.a ./test/build/
