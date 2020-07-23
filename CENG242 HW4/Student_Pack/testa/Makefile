LDFLAGS=-ansi -pedantic -ggdb3 

all: ; g++ $(LDFLAGS) Particle.cpp Wall.cpp CurvyWall.cpp Cell.cpp MicroOrganism.cpp NucleoBase.cpp Triangular.cpp Circular.cpp Squadratic.cpp Tissue.cpp maintest.cpp  -o hw4
run: ;./hw4 inputTest/cells1.txt inputTest/microorganisms1.txt > output.txt
run2: ;./hw4 inputTest/cells1.txt inputTest/microorganisms2.txt > output.txt
valgrind: ; valgrind --leak-check=full --verbose --show-leak-kinds=all --track-origins=yes  ./hw4 inputTest/cells1.txt inputTest/microorganisms1.txt
clean: ; rm -rf hw4
test: ; diff output.txt out.txt || exit 0
test2: ; diff output.txt out2.txt || exit 0