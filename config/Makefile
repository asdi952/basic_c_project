
SRC_PATH = ../src
OBJ_PATH = build
BIN_PATH = bin
#--------------------------
EXE_NAME = run
COMPILER = tcc
#--------------------------
INCLUDE_DIRECTORIES = $(SRC_PATH)
#--------------------------

src_files = $(wildcard  $(SRC_PATH)/*.c)
obj_files = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(src_files))

include_directories = $(addprefix -I,$(INCLUDE_DIRECTORIES))
#--------------------------


run: $(BIN_PATH)/$(EXE_NAME).exe
	@echo RUNNING --#
	@$<

$(BIN_PATH)/$(EXE_NAME).exe: $(obj_files)
	@echo LINKING --#
	@$(COMPILER) $^ -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@$(COMPILER) -c $< -o $@


clear:
	@del $(BIN_PATH)
	@del $(OBJ_PATH)
	

echo:
	@echo  asd $(src_files)
	@echo  asd $(obj_files)
	@echo  asd $(include_directories)

