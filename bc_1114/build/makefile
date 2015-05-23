#
# Notes:
#
# 1.
# Example is from launchpad.net gcc ARM compiler examples.
#
# 2.
# Instead of building objects in another directory, you could try building
# objects from sources in another directory: put your makefile in the directory
# where the objects are going to be and tell make to look for sources elsewhere
# using VPATH. This works best if all object files are supposed to end up in
# the same directory.
#
# 3.
# Options:
#
# -nostartfiles
# -nodefaultlibs
# -nostdlib
# -pie
# -Wl option
# -Xlinker option
#
#
# 4.
# Generate source listing, c and asm
#
# -Wa,-adhln -g
#
# The options:
# -g: Produce debugging information
# -Wa,option: Pass option as an option to the assembler
#
# -adhln:
#  a: turn on listings
#  d: omit debugging directives; n: omit forms processing
#  h: include high-level source
#  l: include assembly
#
#
# Or another approach:
# We know that -S option makes gcc output assembly code in a .s file so we
# can examine. I'd like to know can I have gcc generate .s file with
# original C/C++ source code listed side by side(but in comment blocks)
# with assembly code. The benefit for this is the reader can easily know
# which  C/C++ statement corresponds to which assembly(assembler) code.
# 
# Is there any options to enable this? If yes, since what version of gcc
# is it supported?
#
#All of them.
#
#-g -Wa,-adhls
#


# TODO
#
# 1.
# Maybe you have to add 
# STARTUP_DEFS=-D__STARTUP_CLEAR_BSS -D__START=main
# if use standard lib or init srcipts ?


IDIRS = -I. -I../src -I../src/sys -I../src/lpc_chip_11cxx_library/inc -I../src/lpcexpresso_11c24_board_library/inc


SRCS_CHIP =    adc_11xx.c            \
               chip_11xx.c           \
               clock_11xx.c          \
               gpio_11xx_1.c         \
               gpio_11xx_2.c         \
               gpiogroup_11xx.c      \
               i2c_11xx.c            \
               iocon_11xx.c          \
               pinint_11xx.c         \
               pmu_11xx.c            \
               ring_buffer.c         \
               ssp_11xx.c            \
               sysctl_11xx.c         \
               sysinit_11xx.c        \
               timer_11xx.c          \
               uart_11xx.c           \
               wwdt_11xx.c           
               

SRCS_BOARD =   board_sysinit.c       \
               board.c               

SRCS_SYS =     cr_startup_lpc11xx.c  \
               crp.c                 \
               sysinit.c               


# maybe not needed, because .o are build in ./build
#OBJ_DIR = . 
#
#OBJ_CHIP =     adc_11xx.o            \
               chip_11xx.o           \
               clock_11xx.o          \
               gpio_11xx_1.o         \
               gpio_11xx_2.o         \
               gpiogroup_11xx.o      \
               i2c_11xx.o            \
               iocon_11xx.o          \
               pinint_11xx.o         \
               pmu_11xx.o            \
               ring_buffer.o         \
               ssp_11xx.o            \
               sysctl_11xx.o         \
               sysinit_11xx.o        \
               timer_11xx.o          \
               uart_11xx.o           \
               wwdt_11xx.o           
               

#OBJ_BOARD =    board_sysinit.o       \
               board.o               

#OBJ_SYS =      cr_startup_lpc11xx.o  \
               crp.o                 \
               sysinit.o                


VPATH = ../src ../src/sys ../src/lpc_chip_11cxx_library/src ../src/lpcexpresso_11c24_board_library/src  


# Flags specified for LPCXpresso code.
#

# For references, from orig blinky project
#
#Summary MCU C compiler:
#
#-D__REDLIB__
#-DDEBUG
#-D__CODE_RED
#-D__USE_LPCOPEN
#-DCORE_M0
#
#-O0
#-g3
#-Wall
#-c
#-fmessage-length=0
#
#-fno-builtin
#-ffunction-sections
#-fdata-sections
#-mcpu=cortex-m0
#-mthumb
#-D__REDLIB__
#-specs=redlib.specs

#Summary MCU Assembler:
#
#-c
#-x assembler-with-cpp
#-D__REDLIB__
#-DDEBUG
#-D__CODE_RED
#-g3
#-mcpu=cortex-m0
#-mthumb
#-D__REDLIB__
#-specs=redlib.specs

#Summary MCU Linker:
#
#-nostdlib
#-Xlinker
#-Map="nxp_lpcxpresso_11c24_periph_blinky.map"
#-Xlinker --gc-sections
#-mcpu=cortex-m0
#-mthumb
#-T"nxp_lpcxpresso_11c24_periph_blinky_Debug.ld"



# -D__CODE_RED - Use bool redefinition and open to use "Enable Code Read Protect"

# -DCORE_M0 - only warns in LPC code that M0 is not set for compiler.
#             Set here for keep compatibility.
#
# -D__USE_LPCOPEN - If also not defined NO_BOARD_LIB it inlcude board.h
#
# -D__REDLIB__ - Define the entry point for the application.
#                If define it means: __main() is the entry point for Redlib
#                based applications.
#                The main() is the entry point for Newlib based applications
#                We use newlib
# 
LPC_FLAGS = -DCORE_M0 -D__USE_LPCOPEN 


# Soruce listing
#SRC_LIST = -Wa,-adhln -g
#SRC_LIST = -Wa,-adhln -g
# -g to get C source listing by objdump.
#SRC_LIST = -g
SRC_LIST = -g3


# Selecting Core
CORTEX_M=0

# Use newlib-nano. To disable it, specify USE_NANO=
# arek: seems to be use or not nano change nothing if you not use call to nano.
#USE_NANO=--specs=nano.specs
USE_NANO=

# Use seimhosting or not
# Users can choose to use or not use semihosting by following instructions.
# semihosting
# If you need semihosting, linking like:
#$ arm-none-eabi-gcc --specs=rdimon.specs $(OTHER_LINK_OPTIONS)
#
# non-semihosting/retarget
# If you are using retarget, linking like:
#$ arm-none-eabi-gcc --specs=nosys.specs $(OTHER_LINK_OPTIONS)

#USE_SEMIHOST=--specs=rdimon.specs
#USE_NOHOST=--specs=nosys.specs
USE_SEMIHOST=
USE_NOHOST=



# -nostartfiles
# -nodefaultlibs
# -nostdlib
# USE_NO = -nostartfiles -nodefaultlibs -nostdlib 
# USE_NO = -nostartfiles  # ok
# USE_NO = -nostdlib # undefined reference to `__aeabi_uidiv'
# USE_NO = -nodefaultlibs # undefined reference to `__aeabi_uidiv'
USE_NO =


CORE=CM$(CORTEX_M)
BASE=.

# Compiler & Linker
CC=C:\arm\launchpad\bin\arm-none-eabi-gcc
CXX=C:\arm\launchpad\bin\arm-none-eabi-g++

# Options for specific architecture
ARCH_FLAGS=-mthumb -mcpu=cortex-m$(CORTEX_M)

#todo arek probably to remove
# Startup code
# STARTUP=$(BASE)/startup/startup_ARM$(CORE).S

# -Os -flto -ffunction-sections -fdata-sections to compile for code size
#CFLAGS=$(ARCH_FLAGS) $(STARTUP_DEFS) $(IDIRS) $(LPC_FLAGS) -Os -flto -ffunction-sections -fdata-sections
# No $(STARTUP_DEFS)
CFLAGS=$(ARCH_FLAGS) $(IDIRS) $(LPC_FLAGS) $(SRC_LIST) -flto -ffunction-sections -fdata-sections
CXXFLAGS=$(CFLAGS)

# Link for code size
GC=-Wl,--gc-sections

# Create map file
MAP=-Wl,-Map=$(NAME).map



NAME=bc_1114

# After analize seems to be not necessary. This is specific for launchpad
# examples initialization.
#STARTUP_DEFS=-D__STARTUP_CLEAR_BSS -D__START=main

#LDSCRIPTS=-L. -L$(BASE)/ldscripts -T nokeep.ld
LDSCRIPTS=-L. -L$(BASE)/ldscripts -T bc_1114_Debug.ld
# works: LFLAGS=$(USE_NANO) $(USE_NOHOST) $(LDSCRIPTS) $(GC) $(MAP) 
LFLAGS=$(USE_NANO) $(USE_NOHOST) $(USE_NO) $(LDSCRIPTS) $(GC) $(MAP)


# This is original launchpad approach. from .c to .axf without
# specify .o files.
#
#$(NAME)-$(CORE).axf: $(NAME).c $(STARTUP)
#	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@
#
# Working. There is no separate .o visible.
all : $(NAME).axf
#
$(NAME).axf: $(NAME).c $(SRCS_SYS) $(SRCS_CHIP) $(SRCS_BOARD)
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@








# Try separate line for .o
#all : $(NAME).axf
#
#%.o: %.c 
#	$(CC) $(CFLAGS) -o $@ -c $<
#
#%.o: $(SRCS_SYS) $(SRCS_BOARD) $(SRCS_CHIP) $(NAME).c 
#	$(CC) $(CFLAGS) -c $<
#
#$(NAME).axf: $(NAME).o $(OBJ_CHIP) $(OBJ_BOARD) $(OBJ_SYS) 
#	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@




# bc_pc_emu_c make based approach
#all : $(NAME).axf

#%.o: %.c 
#	$(CC) $(CFLAGS) -o $@ -c $<

#%.o: $(NAME).c $(SRCS_CHIP) $(SRCS_BOARD) $(SRCS_SYS)
#	$(CC) $(CFLAGS) -c $<

#$(NAME).axf: $(NAME).o $(OBJ_CHIP) $(OBJ_BOARD) $(OBJ_SYS) 
#	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@





clean: 
	rm -f $(NAME)*.axf *.map *.o
