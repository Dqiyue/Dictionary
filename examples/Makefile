CXX = g++
CXXFLAGS += -std=c++11 -I.. -fpermissive
LDFLAGS += -L/usr/local/lib -Wl,--no-as-needed -Wl,--as-needed -ldl

all: test

test: test.o
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	rm -f *.o