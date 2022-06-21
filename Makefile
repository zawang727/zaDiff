LINK_TARGET = test_me.exe

OBJS = fileReader.o \
	fileDiffSolver.o \
	fileDiffSolverByLine.o \
	printUtils.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

$(LINK_TARGET) : $(OBJS)
	g++ -g -o $@ main.cpp $^

%.o : %.cpp
	g++ -g -o $@ -c $<

fileReader.o : fileReader.h programOptions.h
printUtils.o : printUtils.h programOptions.h
fileDiffSolver.o : fileDiffSolver.h
fileDiffSolverByLine.o : fileDiffSolverByLine.h


all : $(LINK_TARGET)
	echo All done
	
.PHONY:clean
clean:
	rm -f $(REBUILDABLES)
	echo Clean done
	

