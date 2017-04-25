CXX=clang++
override CXXFLAGS+=-std=c++11 -g

.PHONY: all pp

all : tst

tst : tst.cpp fnwrap.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

pp :
	$(CXX) $(CXXFLAGS) -E -o - tst.cpp
