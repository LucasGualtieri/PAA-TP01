CC = g++

CFLAGS = -std=c++20 -O0

SRC = include/RandomEulerian.hpp src/RandomEulerian.cpp include/progressBar.hpp src/progressBar.cpp

OBJ = $(SRC:.cpp=.o)

# TESTS = tests/test_main.cpp tests/test_naive.cpp tests/test_tarjan.cpp tests/test_fleury.cpp

OUT = bin/program
TEST = bin/test

# Cria a pasta bin se ela não existir
$(shell mkdir -p bin)

all: $(OUT)
	./$(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

# tests: $(OUT)
# 	$(CC) $(CFLAGS) -o bin/test $(TESTS)
# 	./bin/test

naive:
	$(CC) $(CFLAGS) -o $(TEST) $(SRC) tests/test_naive.cpp src/fleury_naive.cpp
	./$(TEST)

tarjan:
	$(CC) $(CFLAGS) -o $(TEST) $(SRC) tests/test_tarjan.cpp src/fleury_tarjan.cpp
	./$(TEST)

tarjanvsnaive:
	$(CC) $(CFLAGS) -o $(TEST) $(SRC) tests/test_tarjanvsnaive.cpp src/fleury_tarjan.cpp src/fleury_naive.cpp
	./$(TEST)

# random: $(OUT)
# 	$(CC) $(CFLAGS) -o bin/test tests/test_random_eulerian.cpp include/RandomEulerian.hpp src/RandomEulerian.cpp
# 	./bin/test

# bar: $(OUT)
# 	$(CC) $(CFLAGS) -o bin/test tests/test_progressBar.cpp include/progressBar.hpp src/progressBar.cpp
# 	./bin/test

clean:
	rm -rf $(OBJ) $(OUT) $(TEST)
