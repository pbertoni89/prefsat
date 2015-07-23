CXX=g++
CXXFLAGS=-O3 -Wall -Wextra -DNDEBUG -DNLOGPRECO -DNSTATSPRECO $(PROF)
all: targets
targets: precosat
clean: clean-other clean-config
clean-config:
	rm -f makefile precocfg.hh 
clean-other:
	rm -f precosat *.o 
	rm -f *.gcno *.gcda cscope.out gmon.out *.gcov
	rm -f log/*.log
feedback:
	make clean-other
	touch makefile
	PROF=-fprofile-generate make targets
	--./precosat 
	touch makefile
	PROF=-fprofile-use make targets
precosat: precomain.o precosat.o precobnr.o 
	$(CXX) $(CXXFLAGS) -o precosat precomain.o precosat.o precobnr.o 
precosat.o: precosat.hh precosat.cc makefile
	$(CXX) $(CXXFLAGS) -c precosat.cc
precobnr.o: precobnr.cc precobnr.hh precocfg.hh
	$(CXX) $(CXXFLAGS) -c precobnr.cc
precomain.o: precomain.cc precocfg.hh precobnr.hh
	$(CXX) $(CXXFLAGS) -c precomain.cc
precocfg.hh: makefile VERSION mkconfig precosat.hh precosat.cc
	rm -f $@; ./mkconfig > $@
.PHONY: all clean clean-config clean-other feedback targets
