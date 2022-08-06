PROJDIR := $(realpath $(CURDIR)/..)
SOURCEDIR := $(PROJDIR)/Sources
BUILDDIR := $(PROJDIR)/Build
LINK_TARGET = test_me.exe

VERBOSE = TRUE

all:
    +$(MAKE) -C Solver

OBJS = fileReader.o \
	printUtils.o \
	lineDiff.o \
	fileDiffSolver.o \
	fileDiffSolverByLine.o \
	fileDiffSolverGreedy.o \
	fileDiffSolverHuntSzymanski.o


REBUILDABLES = $(OBJS) $(LINK_TARGET)

$(LINK_TARGET) : $(OBJS)
	g++ -g -o $@ main.cpp $^

%.o : %.cpp
	g++ -g -o $@ -c $<

fileReader.o : fileReader.h programOptions.h
printUtils.o : printUtils.h programOptions.h
lineDiff.o : programOptions.h printUtils.h
fileDiffSolver.o : fileDiffSolver.h
fileDiffSolverByLine.o : fileDiffSolverByLine.h
fileDiffSolverGreedy.o : lineDiff.h fileDiffSolver.h
fileDiffSolverHuntSzymanski.o : lineDiff.o fileDiffSolver.h


all : $(LINK_TARGET)
	echo All done
	
.PHONY:clean
clean:
	del -f $(REBUILDABLES)
	rm -f $(REBUILDABLES)
	echo Clean done
	

