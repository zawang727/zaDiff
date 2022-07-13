LINK_TARGET = test_me.exe

OBJS = fileReader.o \
	fileDiffSolver.o \
	fileDiffSolverByLine.o \
	printUtils.o \
	lineDiff.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

$(LINK_TARGET) : $(OBJS)
	g++ -g -o $@ main.cpp $^

%.o : %.cpp
	g++ -g -o $@ -c $<

fileReader.o : fileReader.h programOptions.h
printUtils.o : printUtils.h programOptions.h
fileDiffSolver.o : fileDiffSolver.h
fileDiffSolverByLine.o : fileDiffSolverByLine.h
lineDiff.o : programOptions.h printUtils.h


all : $(LINK_TARGET)
	echo All done
	
.PHONY:clean
clean:
	del -f $(REBUILDABLES)
	rm -f $(REBUILDABLES)
	echo Clean done
	

