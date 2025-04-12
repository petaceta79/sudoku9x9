program.exe: sudoku.o main.o 
	g++ -o sudoku_solver.exe sudoku.o main.o

sudoku.o: sudoku.cc sudoku.hh
	g++ -c sudoku.cc

main.o: main.cc
	g++ -c main.cc

clean:
	rm -f *.o program.exe