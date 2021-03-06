# version of this Makefile
MAKEFILE_VER=		0.6.4



# make options
MAKEFLAGS+=			-s



# NOTE: search for 'CUSTOM' text




# CUSTOM output executable file
OUT_FILE=			bowling

# CUSTOM paths
INC_DIR=			src
SRC_DIR=			src
LIB_DIR=			lib

# CUSTOM libs
LIBS_REL=			-l cxxtools
LIBS_STA=			$(LIBS_REL)
LIBS_DEB=			$(LIBS_REL)
LIBS_TES=			$(LIBS_REL) -l cxxtools-unit



# basic path
BUILD_DIR=			BUILD
RELEASE_DIR=		$(BUILD_DIR)/release
STATIC_DIR=			$(BUILD_DIR)/static
DEBUG_DIR=			$(BUILD_DIR)/debug
TEST_DIR=			$(BUILD_DIR)/test



# compiler and linker
CC=					g++
LD=					g++

# rm
RM=					rm -f



# flags
PLATFORM_FLAGS=		-m64

CC_FLAGS=			-pipe -ansi -pedantic -Wall -Wextra $(PLATFORM_FLAGS) -I$(INC_DIR)
LD_FLAGS=			-L$(LIB_DIR) $(PLATFORM_FLAGS)

RELEASE_FLAGS=		-O3 -s				# optimization and remove all symbol table
#RELEASE_FLAGS=		-O3 -ggdb -g3		# keep debug information but optimize so that the code is fast like a release
STATIC_LD_FLAGS=	-static -static-libgcc -static-libstdc++ -pthread
DEBUG_FLAGS=		-Og -ggdb -g3    	# some debug optimization and increase debug level to 3
TEST_FLAGS=			$(DEBUG_FLAGS)



# commands
ifeq ($(MAKECMDGOALS), clean)
	GOAL=			Clean
else ifeq ($(MAKECMDGOALS), debug)
	GOAL=			Debug
	OUT_DIR=		$(DEBUG_DIR)
	CC_CMD_ARGS=	$(DEBUG_FLAGS) $(CC_FLAGS)
	LD_CMD_ARGS=	$(DEBUG_FLAGS) $(LD_FLAGS) $(LIBS_DEB)
else ifeq ($(MAKECMDGOALS), test)
	GOAL=			Test
	OUT_DIR=		$(TEST_DIR)
	CC_CMD_ARGS=	$(TEST_FLAGS) $(CC_FLAGS)
	LD_CMD_ARGS=	$(TEST_FLAGS) $(LD_FLAGS) $(LIBS_TES)
else ifeq ($(MAKECMDGOALS), static)
	GOAL=			Static
	OUT_DIR=		$(STATIC_DIR)
	CC_CMD_ARGS=	$(RELEASE_FLAGS) $(CC_FLAGS)
	LD_CMD_ARGS=	$(RELEASE_FLAGS) $(STATIC_LD_FLAGS) $(LD_FLAGS) $(LIBS_STA)
else
	GOAL=			Release
	OUT_DIR=		$(RELEASE_DIR)
	CC_CMD_ARGS=	$(RELEASE_FLAGS) $(CC_FLAGS)
	LD_CMD_ARGS=	$(RELEASE_FLAGS) $(LD_FLAGS) $(LIBS_REL)
endif


# colors
# https://wiki.archlinux.org/index.php/Bash/Prompt_customization#Escapes_between_command_input_and_output
# https://en.wikipedia.org/wiki/ANSI_escape_code#CSI_codes
NORMAL=				"\\033[0;39m"
GREEN=				"\\033[1;32m"
WHITE=				"\\033[1;37m"
YELLOW=				"\\033[1;33m"
RED=				"\\033[1;31m"
BLUE=				"\\033[1;34m"
CYAN=				"\\033[1;36m"
PINK=				"\\033[1;35m"

SPACE=				"\\033[70G"
SPACE="\t\t"
# note this way to obtain actual column
# echo -en "\E[6n"; read -sdR CURPOS; CURPOS=`echo ${CURPOS} | cut -d '[' -f 2 | cut -d ';' -f 1`; echo -en "\\033[${CURPOS};70f"
SAVE_CUR_POS=		"\\033[s"
RESTORE_CUR_POS=	"\\033[u"



# output
ECHO_DONE=			$(SPACE)$(GREEN)DONE$(NORMAL)
ECHO_SHIT=			$(SPACE)${RED}SHIT$(NORMAL)
CHECK=				&& echo $(ECHO_DONE) || (echo && echo $(ECHO_SHIT) && exit 1)



################################################################################
#--- main target
all:				release

release:			INFO_TRG CMD_PREREQ INFO_VARS INFO_CC CMD_COMPILE INFO_LD CMD_LINK
	@echo
	@echo "Hint: run with './$(OUT_DIR)/$(OUT_FILE)'"
	@echo

static:				INFO_TRG CMD_PREREQ INFO_VARS INFO_CC CMD_COMPILE INFO_LD CMD_LINK
	@echo
	@echo "Hint: run with './$(OUT_DIR)/$(OUT_FILE)'"
	@echo

debug:				INFO_TRG CMD_PREREQ INFO_VARS INFO_CC CMD_COMPILE INFO_LD CMD_LINK
	@echo
	@echo "Hint: debug with 'ddd $(OUT_DIR)/$(OUT_FILE)'"
	@echo

test:				INFO_TRG CMD_PREREQ INFO_VARS INFO_CC CMD_COMPILE_TEST INFO_LD CMD_LINK
	@echo
	@echo "Hint: test with './$(OUT_DIR)/$(OUT_FILE)'"
	@echo



################################################################################
#--- CUSTOM dependence files

CMD_COMPILE:		Game $(OUT_DIR)/main.o
CMD_COMPILE_TEST:	BowlingTest

BowlingTest:		Game $(INC_DIR)/BowlingTest.h $(OUT_DIR)/BowlingTest.o
Game:				$(INC_DIR)/Game.h $(OUT_DIR)/Game.o



################################################################################
#--- redefine the implicit rule to compile
$(OUT_DIR)/%.o:		$(SRC_DIR)/%.cpp
	@echo -n ${GREEN}"   + "${WHITE}$(SRC_DIR)/$*.cpp$(NORMAL) -o $(OUT_DIR)/$*.o "... "
	$(CC) -c $(SRC_DIR)/$*.cpp $(CC_CMD_ARGS) -o $(OUT_DIR)/$*.o $(CHECK)

CMD_LINK:
	@echo -n ${GREEN}"   + "${WHITE} $(OUT_DIR)"/*.o"$(NORMAL) -o $(OUT_DIR)/$(OUT_FILE) "... "
	$(LD) $(OUT_DIR)/*.o $(LD_CMD_ARGS) -o $(OUT_DIR)/$(OUT_FILE) $(CHECK)



################################################################################
CMD_PREREQ:
	mkdir -p $(RELEASE_DIR)
	mkdir -p $(STATIC_DIR)
	mkdir -p $(DEBUG_DIR)
	mkdir -p $(TEST_DIR)



################################################################################
clean:				INFO_TRG
	@echo
	@echo -n ${RED}"   - "${WHITE}$(RM) $(RELEASE_DIR)"/*.o" $(RELEASE_DIR)/$(OUT_FILE)$(NORMAL)
	$(RM) $(RELEASE_DIR)/*.o $(RELEASE_DIR)/$(OUT_FILE)$(CHECK)
	@echo -n ${RED}"   - "${WHITE}$(RM) $(STATIC_DIR)"/*.o" $(STATIC_DIR)/$(OUT_FILE)$(NORMAL)
	$(RM) $(STATIC_DIR)/*.o $(STATIC_DIR)/$(OUT_FILE)$(CHECK)
	@echo -n ${RED}"   - "${WHITE}$(RM) $(DEBUG_DIR)"/*.o" $(DEBUG_DIR)/$(OUT_FILE)$(NORMAL)
	$(RM) $(DEBUG_DIR)/*.o $(DEBUG_DIR)/$(OUT_FILE)$(CHECK)
	@echo -n ${RED}"   - "${WHITE}$(RM) $(TEST_DIR)"/*.o" $(TEST_DIR)/$(OUT_FILE)$(NORMAL)
	$(RM) $(TEST_DIR)/*.o $(TEST_DIR)/$(OUT_FILE)$(CHECK)
	@echo



################################################################################
INFO_TRG:
	@echo $(YELLOW)"= "$(GOAL)" ="$(NORMAL)

INFO_VARS:
	@echo
	@echo $(YELLOW)"Variables used to build:"$(NORMAL)
	@echo $(BLUE)CC_FLAGS=	$(CC_FLAGS)$(NORMAL)
	@echo $(BLUE)LD_FLAGS=	$(LD_FLAGS)$(NORMAL)

INFO_CC:
	@echo
	@echo $(YELLOW)"Command used to build:"$(NORMAL)
	@echo    $(BLUE)$(CC)" <files> "$(CC_CMD_ARGS) -c$(NORMAL)

INFO_LD:
	@echo
	@echo $(YELLOW)"Command used to link:"$(NORMAL)
	@echo    $(BLUE)$(LD)" <files> "$(LD_CMD_ARGS)$(NORMAL)



# End
