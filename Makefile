
SRC_setsched = main.c
OBJ_setsched = $(SRC_setsched:.c=.o)
BIN_setsched = setsched

SRC_CPU_stress = cpu_stress.c cpu_intensive.c
OBJ_CPU_stress = $(SRC_CPU_stress:.c=.o)
BIN_CPU_stress = cpu_stress

CC = gcc
LD = $(CC)

ALL_CFLAGS = -Iinclude $(CFLAGS)
ALL_LDFLAGS = 

VPATH = src src/cpu_stress

HEADERS = $(shell find include -name \*.h )

# $(info $(HEADERS) )

%.o: %.c $(HEADERS)
	$(CC) $(ALL_CFLAGS) -c $< -o $@

setsched: $(OBJ_setsched)
	$(LD) $(OBJ_setsched) -o $(BIN_setsched) $(ALL_LDFLAGS)

cpu_stress: $(OBJ_CPU_stress)
	$(LD) $(OBJ_CPU_stress) -o $(BIN_CPU_stress) $(ALL_LDFLAGS)

.PHONY: all clean 

all: cpu_stress setsched

clean:
	rm -f *.o *.out $(BIN_setsched) $(BIN_CPU_stress)