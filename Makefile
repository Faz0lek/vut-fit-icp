# Authors: Martin Kostelník (xkoste12), Adam Gajda (xgajda07)

NAME = icp
ZIPFILE = xgajda07-xkoste12.zip

default:
	qmake -o ./src/Makefile ./src/$(NAME).pro
	$(MAKE) -C src
	
run:
	./src/$(NAME)
	
run-win:
	./src/$(NAME).exe
	
doxygen:
	doxygen ./doc/Doxyfile
	
clean:
	rm -frv ./doc/!(Doxyfile) ./src/!(*.cpp|*.h|$(NAME).pro|mainwindow.ui)


pack: clean default clean
	zip -9rv $(ZIPFILE) src examples doc README.txt Makefile
