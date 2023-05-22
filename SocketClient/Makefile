CC = gcc
CFLAGS = -Wall -Werror -Og

SRC_DIR = .
OBJ_DIR = obj

INCLUDE_PATH = -I./ -I../Common
LIB_NAME = libsocket_common.so
BIN_DIR = ../bin

BIN = client

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(BIN_DIR)/$(BIN)

$(BIN_DIR)/$(BIN): $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(BIN_DIR)/$(LIB_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(BIN_DIR)/$(BIN) $(OBJ_DIR)/*.o
