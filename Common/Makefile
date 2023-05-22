CC = gcc
CFLAGS = -Og -Wall -Werror

SRC_DIR = .
OBJ_DIR = obj

LIB_NAME = libsocket_common.so
LIB_DIR = ../bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(LIB_DIR)/$(LIB_NAME)

$(LIB_DIR)/$(LIB_NAME): $(OBJ_FILES) | $(LIB_DIR)
	$(CC) $(CFLAGS) -shared -o $@ $^ -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

clean:
	rm -f $(OBJ_DIR)/*.o $(LIB_DIR)/$(LIB_NAME)