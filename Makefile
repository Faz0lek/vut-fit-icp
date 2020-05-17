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
	rm -frv ./doc/latex ./doc/html ./src/*.o ./src/$(NAME) ./src/Makefile ./src/moc_* ./src/ui_* ./src/.qmake.stash ./*.zip


pack: default clean
	zip -9rv $(ZIPFILE) src examples doc README.txt Makefile
