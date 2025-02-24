CC = g++

CFLAGS = -std=c++20 -O0

SRC = src/main.cpp src/naive.cpp src/tarjan.cpp src/fleury.cpp src/utils.cpp

OBJ = $(SRC:.cpp=.o)

TESTS = tests/test_main.cpp tests/test_naive.cpp tests/test_tarjan.cpp tests/test_fleury.cpp

OUT = bin/program

# Cria a pasta bin se ela não existir
$(shell mkdir -p bin)

all: $(OUT)
	./$(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

tests: $(OUT)
	$(CC) $(CFLAGS) -o bin/test $(TESTS)
	./bin/test

random: $(OUT)
	$(CC) $(CFLAGS) -o bin/test tests/test_random_eulerian.cpp include/RandomEulerian.hpp src/RandomEulerian.cpp
	./bin/test

naive: $(OUT)
	$(CC) $(CFLAGS) -o bin/test tests/test_naive.cpp include/fleury_naive.hpp src/fleury_naive.cpp  include/RandomEulerian.hpp src/RandomEulerian.cpp include/progressBar.hpp src/progressBar.cpp
	./bin/test

tarjan: $(OUT)
	$(CC) $(CFLAGS) -o bin/test tests/test_tarjan.cpp include/fleury_tarjan.hpp src/fleury_tarjan.cpp
	./bin/test

bar: $(OUT)
	$(CC) $(CFLAGS) -o bin/test tests/test_progressBar.cpp include/progressBar.hpp src/progressBar.cpp
	./bin/test

clean:
	rm -rf $(OBJ) $(OUT) bin/test
