CC=gcc
SHELL:=$(shell which bash) -e -o pipefail
UNAME_S:=$(shell uname -s)
_CFLAGS=-Wall -Wextra -Werror -Wshadow -Winline -D_GNU_SOURCE -std=c99 -g

BIN_DIR=$(CURDIR)/bin
SRC_DIR=$(CURDIR)/src
SCRIPT_DIR=$(CURDIR)/script

create:
	@echo "Creating 1GB file :"
	./$(SCRIPT_DIR)/create1GB.sh

build:
	$(CC) -o $(BIN_DIR)/main $(SRC_DIR)/main.c
