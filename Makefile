CFLAGS=-Wall -std=c11
SRC_DIR=./src
OBJ_DIR=./obj
BIN_DIR=./bin
SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
HEADERS=$(SRC_DIR)/ycc.h
TARGET=$(BIN_DIR)/*

ycc: $(OBJS)
	$(CC) -o $(BIN_DIR)/ycc $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

test: ycc
	make format
	$(BIN_DIR)/ycc --test
	./test.sh

debug: $(SRCS)
	$(CC) -g -o $(BIN_DIR)/dycc $(SRCS) $(LDFLAGS)

clean:
	rm -f $(OBJ_DIR)/*

format:
	clang-format -i $(SRC_DIR)/*
