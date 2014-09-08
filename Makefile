CC=gcc
SHELL:=$(shell which bash) -e -o pipefail
UNAME_S:=$(shell uname -s)
_CFLAGS=-Wall -Wextra -Werror -Wshadow -Winline -D_GNU_SOURCE -std=c99 -g

BIN_DIR=$(CURDIR)/bin
SRC_DIR=$(CURDIR)/src
SCRIPT_DIR=$(CURDIR)/scripts

# All header files in libraries
INCLUDES=-I$(SRC_DIR) -I$(CURDIR) \
	 -I$(CURDIR)/deps/uthash \

# All .c files in src folder
_SOURCES=$(shell find $(SRC_DIR) -type f -iname '*.[c]')

# Create 1GB file
create:
	@echo "Creating 1GB file :"
	$(SCRIPT_DIR)/create1GB.sh

# Build
build:
	-mkdir -p $(BIN_DIR)
	#$(CC) -o $(BIN_DIR)/main $(SRC_DIR)/main.c $(INCLUDES) $(_SOURCES)
	$(CC) -o $(BIN_DIR)/main $(_SOURCES) $(INCLUDES)

clean:
	@echo "Deleting bin folder"
	rm -rf $(BIN_DIR)/*

