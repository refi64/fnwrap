CXX=clang++

.PHONY: all pp

all : tst

tst : tst.cpp fnwrap.hpp
	$(CXX) -g -std=c++11 -o $@ $<

pp :
	$(CXX) -std=c++11 -E -o - tst.cpp
