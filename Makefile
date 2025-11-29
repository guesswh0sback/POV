# --- Variables globales ---
MCU = atmega328p
F_CPU = 13000000
PORT = /dev/ttyACM0
PROGRAMMER = usbasp

# MAIN SELECTION 
MAIN ?= display_clk_main.c

# Directory structure
BUILD_DIR = build
MAIN_DIR = main_s

# Source files
MAIN_FILE = $(MAIN_DIR)/$(MAIN)
SRCS := $(wildcard src/*.c) # prends tous les .c de src/

# Object files 
#(strip to avoid accidental trailing whitespace)
OBJS := $(strip $(SRCS:%.c=$(BUILD_DIR)/%.o)) # transforme chaque src/.c en build/src/.o
MAIN_OBJ := $(strip $(BUILD_DIR)/$(MAIN_DIR)/$(MAIN:.c=.o)) # crée le chemin de l'objet principal (compilé séparément)

# Derive ELF/BIN directly from MAIN to avoid basename/whitespace issues
ELF := $(BUILD_DIR)/$(MAIN:.c=.elf)
BIN := $(BUILD_DIR)/$(MAIN:.c=.bin)

# Compiler flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
CFLAGS += -I.

# --- REGLES PRINCIPALES ---

# Compilation
all: $(BIN)

$(BUILD_DIR):
ifeq ($(OS),Windows_NT)
	@cmd /C if not exist "$(subst /,\\,$(BUILD_DIR))" mkdir "$(subst /,\\,$(BUILD_DIR))"
else
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(dir $(OBJS))
	@mkdir -p $(dir $(MAIN_OBJ))
endif

# Pattern rule: compile each .c into its corresponding .o
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
ifeq ($(OS),Windows_NT)
	@cmd /C if not exist "$(subst /,\\,$(dir $@))" mkdir "$(subst /,\\,$(dir $@))"
else
	@mkdir -p $(dir $@) 2>/dev/null || true
endif
	avr-gcc $(CFLAGS) -c $< -o $@

$(ELF): $(OBJS) $(MAIN_OBJ)
	avr-gcc $(CFLAGS) -o "$(ELF)" $(OBJS) $(MAIN_OBJ)

$(BIN): $(ELF)
	avr-objcopy -O ihex -R .eeprom "$(ELF)" "$(BIN)"

# Téléversement
install: $(BIN)
ifeq ($(OS),Windows_NT)
	@avrdude -v -p $(MCU) -c $(PROGRAMMER) -U flash:w:$(BIN):i
else
	@avrdude -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -U flash:w:$(BIN):i
endif

# Nettoyage
clean:
ifeq ($(OS),Windows_NT)
	@cmd /C if exist "$(subst /,\\,$(BUILD_DIR))" rd /s /q "$(subst /,\\,$(BUILD_DIR))"
else
	@rm -rf $(BUILD_DIR) 2>/dev/null || rmdir /s /q $(BUILD_DIR)
endif

# Cibles symboliques
.PHONY: all install clean