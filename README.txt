ICP Project 2019/20 - Application for observing public transportation
    This application was made in order to simulate public transportation more specifically bus lines.

Authors: Martin Kostelník (xkoste12), Adam Gajda (xgajda07)

Makefile supports:
    make - Creates Makefile in ./src/ and builds
    make run - Starts executable in ./src/
    make run-win - Starts executable in ./src/ (Windows variant)
    make doxygen - Generates documentation from ./doc/Doxyfile and ./src/* folders ./doc/html/ and ./doc/latex/
    make clean - Removes everything created with this Makefile
    make pack - executes make and make clean and then zips every necessary file into a zip file
    
Examples:
    streetsfile.csv - contains streets in format: street_name,x1,y1,x2,y2
    linesfile.csv - contains individual bus lines in format: bus_line_number,,street_name1,normalized_distance1,time1,time2,...,,street_name2,normalized_distance1,timeA,timeB...,,.....