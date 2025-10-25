OPZIONI = -Wall -Wfatal-errors -O3
ContoCorrente.exe: ContoCorrente.o driver.o
	g++ -o ContoCorrente.exe ContoCorrente.o driver.o
ContoCorrente.o: ContoCorrente.cpp ContoCorrente.hpp
	g++ -c $(OPZIONI) ContoCorrente.cpp 
driver.o: driver.cpp ContoCorrente.hpp
	g++ -c $(OPZIONI) driver.cpp
clean:
	rm -f *.o ContoCorrente.exe