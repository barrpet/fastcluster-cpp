CXXFLAGS+=-fPIC -I../include

default: fastcluster.o

cxx11: CXXFLAGS += -std=c++11
cxx11: fastcluster.o

cxx98: CXXFLAGS += -std=c++98
cxx98: fastcluster.o

ansi: CXXFLAGS += -ansi
ansi: fastcluster.o

fastcluster_%.o: fastcluster.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

fastcluster.o: fastcluster.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	@rm -fv *.o

purge: clean
