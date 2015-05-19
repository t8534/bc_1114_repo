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

IDIRS = -I. -I../src -I../src/lpc_chip_11cxx_library/inc -I../src/lpcexpresso_11c24_board_library/inc  -I../sys


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
               wwdt_11xx.c           \
               

SRCS_BOARD =   board_sysinit.c       \
               board.c               \

SRCS_SYS =     cr_startup_lpc11xx.c  \
               crp.c                 \
               sysinit.c             \   


# maybe not needed, because .o are build in ./build
OBJ_DIR = . 

OBJ_CHIP =     adc_11xx.o            \
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
               wwdt_11xx.o           \
               

OBJ_BOARD =    board_sysinit.o       \
               board.o               \

OBJ_SYS =      cr_startup_lpc11xx.o  \
               crp.o                 \
               sysinit.o             \   



# Selecting Core
CORTEX_M=0

# Use newlib-nano. To disable it, specify USE_NANO=
USE_NANO=--specs=nano.specs

# Use seimhosting or not
USE_SEMIHOST=--specs=rdimon.specs
USE_NOHOST=--specs=nosys.specs

CORE=CM$(CORTEX_M)
BASE=../..

# Compiler & Linker
CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++

# Options for specific architecture
ARCH_FLAGS=-mthumb -mcpu=cortex-m$(CORTEX_M)

#todo arek probably to remove
# Startup code
STARTUP=$(BASE)/startup/startup_ARM$(CORE).S

# -Os -flto -ffunction-sections -fdata-sections to compile for code size
CFLAGS=$(ARCH_FLAGS) $(STARTUP_DEFS) -Os -flto -ffunction-sections -fdata-sections
CXXFLAGS=$(CFLAGS)

# Link for code size
GC=-Wl,--gc-sections

# Create map file
MAP=-Wl,-Map=$(NAME).map



NAME=bc_1114
STARTUP_DEFS=-D__STARTUP_CLEAR_BSS -D__START=main

LDSCRIPTS=-L. -L$(BASE)/ldscripts -T nokeep.ld
LFLAGS=$(USE_NANO) $(USE_NOHOST) $(LDSCRIPTS) $(GC) $(MAP)

#$(NAME)-$(CORE).axf: $(NAME).c $(STARTUP)
#	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@

$(NAME)-$(CORE).axf: $(NAME).c $(SRCS_CHIP) $(SRCS_BOARD) $(SRCS_SYS) 
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@


clean: 
	rm -f $(NAME)*.axf *.map *.o
