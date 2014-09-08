CC=gcc
SHELL:=$(shell which bash) -e -o pipefail
UNAME_S:=$(shell uname -s)
_CFLAGS=-Wall -Wextra -Werror -Wshadow -Winline -D_GNU_SOURCE -std=c99 -g

BIN_DIR=$(CURDIR)/bin
SRC_DIR=$(CURDIR)/src
SCRIPT_DIR=$(CURDIR)/scripts

INCLUDES=-I$(SRC_DIR) -I$(CURDIR) \
	 -I$(CURDIR)/deps/uthash \

create:
	@echo "Creating 1GB file :"
	$(SCRIPT_DIR)/create1GB.sh

build:
	-mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/main $(SRC_DIR)/main.c $(INCLUDES)

clean:
	@echo "Deleting bin folder"
	rm -rf $(BIN_DIR)/*

