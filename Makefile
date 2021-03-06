CC=gcc
CFLAGS=-Wall -c  -std=gnu11 
LDFLAGS=-pthread  -I ./include/

SRC_DIR=./src
OBJ_DIR=./obj
INC_DIR=./include
BIN_DIR=./bin
DOC_DIR=./doc
GCOV_DIR=./gcov

GCOVFLAGS=-O0 --coverage -lgcov -Wall -g

LCOV_REPORT=report.info

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(SRC:%.c=%.o)
OBJ2= $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC)))
EXEC=miniSHell

GEXEC=$(EXEC).cov 

AR_NAME=archive_$(EXEC).tar.gz


all: $(SRC) $(EXEC)
    
%.o:%.c
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $(OBJ_DIR)/$(notdir $@)

$(EXEC): $(OBJ)
	$(CC) -o $(BIN_DIR)/$@ -Wall $(LDFLAGS) $(OBJ2)

$(GEXEC):
	$(CC) $(GCOVFLAGS) -o $(GCOV_DIR)/$@ -Wall $(LDFLAGS) $(SRC)

doc:
	doxygen $(DOC_DIR)/doxygen.conf

print-%  : ; @echo $* = $($*)

gcov: $(GEXEC)
	# generate some data for gcov by calling the generated binary with various options

	$(GCOV_DIR)/$(GEXEC) -h
	$(GCOV_DIR)/$(GEXEC) -i input -o output -v
	./gcov/miniSHell.cov
	./gcov/miniSHell.cov -c "ls | grep fds && echo ok1 && echo ok2 || echo nok | pwd > cat.txt ; ls -al >> cat.txt ; cat < cat.txt ; cd .. ; cd MiniSHeLL ; wc << ; ls & ; cd fds"
	find ./ -maxdepth 1 -name \*.gcno -exec mv {} $(GCOV_DIR) \;
	find ./ -maxdepth 1 -name \*.gcda -exec mv {} $(GCOV_DIR) \;
	
	gcov -o $(GCOV_DIR) $(GEXEC)
	
	

	lcov -o $(GCOV_DIR)/$(LCOV_REPORT) -c -f -d $(GCOV_DIR)
	genhtml -o $(GCOV_DIR)/report $(GCOV_DIR)/$(LCOV_REPORT)

package: gcov doc all
	rm -rf $(AR_NAME)
	tar cvfz $(AR_NAME) ./*
clean:	
	rm -rf $(OBJ2)

mrproper: clean
	rm -rf $(BIN_DIR)/*
	rm -rf $(DOC_DIR)/latex/
	rm -rf $(DOC_DIR)/html/
	rm -rf $(GCOV_DIR)/*

.PHONY: doc
