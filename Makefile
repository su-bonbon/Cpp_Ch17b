pa17b: pa17b.o List.hpp
	$(CXX) $(CXXFLAGS) pa17b.o -o pa17b

pa17b.o: pa17b.cpp
	$(CXX) $(CXXFLAGS) pa17b.cpp -c

pa17b-wordcount: pa17b-wordcount.o List.hpp
	$(CXX) $(CXXFLAGS) pa17b-wordcount.o -o pa17b-wordcount

pa17b-wordcount.o: pa17b-wordcount.cpp
	$(CXX) $(CXXFLAGS) pa17b-wordcount.cpp -c

pa17b-test: pa17b-test.o List.hpp
	$(CXX) $(CXXFLAGS) test.o -o pa17b-test

pa17b-test.o: test.cpp
	$(CXX) $(CXXFLAGS) test.cpp -c

clean:
	rm -f pa17b.o pa17b pa17b-wordcount pa17b-wordcount.o pa17b-test test.o

turnin:
	turnin -c cs202 -p pa17b -v List.hpp pa17b.cpp Makefile pa17b-wordcount.cpp
