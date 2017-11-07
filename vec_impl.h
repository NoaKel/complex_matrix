# MakeFile for CheckMyFridge
CCC = g++
CXXFLAGS = -Wall -g -std=c++0x
CXXLINK = $(CCC)
LIBS = 
OBJS = main.o complex.o 
RM = rm -f

# Creating the executable (CheckMyFridge)
matrix: $(OBJS)
	$(CXXLINK) -o matrix $(OBJS)
 
# Creating object files using default rules
complex.o: complex.cpp complex.h
main.o: main.cpp vec.h vec_impl.h mat.h mat_impl.h sq_mat.h sq_mat_impl.h complex.h

# Cleaning old files before new make
clean:
	$(RM) matrix *.o *.bak *~ "#"* core
