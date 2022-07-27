#
# This is a basic Makefile template for a Neuromatrix DSP project 
# to be run on Module MB77.07. To compile it you need: 
# * Latest NMSDK installed with utilities in your $PATH
# * NEURO environment variable pointing to NMSDK directory
# * Host GCC (Since nmcpp doesn't support generating deps, 
#	       we use $(CROSS_COMPILE)gcc for that) 
#
# For verbose build run 'make VERBOSE=y'
#

-include colorizer.mk
-include *.dep

.SUFFIXES:

OBJECTS :=  \
	main.o \
	get_byte.o \
	set_byte.o \
	ppm_control.o
	


TARGET=test

# Set this to libeasynmc-nmc dir. Relative or absolute. 
# Make sure you build it prior to building the actual project. 

MB7707_MAC		= 1C-1B-0D-E7-7C-98
#EC-17-66-77-07-00
#1C-1B-0D-E7-7C-98 - MY MAC

CROSS_COMPILE   = arm-module-linux-gnueabi-
NMCPP_FLAGS     = -DNEURO -OPT2 -inline 
ASM_FLAGS       = -soc -Sc -g -Stmp -X-q 
C2ASM_FLAGS     = -soc -q 

#BIG FAT WARNING: easynmc.lib MUST go BEFORE libc
#BIG FAT WARNING: Otherwise argc/argv won't work 

LIBS            =  mb7707lib.lib libc05.lib

BUILDER_FLAGS	= -cK1879.cfg -m -heap=554432 -heap1=0 -heap2=0 -heap3=0 -stack=20000 \
		  -full_names -d1
IDIRS           = -I. -I"$(NEURO)/include"  -I"$(MB7707)/include"
LIBDIR		= -l"$(NEURO)/lib"  -L"$(MB7707)/lib"

.DEFAULT_GOAL=all

all: $(TARGET).abs

%.asmx: %.cpp
	$(SILENT_DEP)$(CROSS_COMPILE)gcc -E -MM $(<) -o$(@).dep
	$(SILENT_NMCPP)nmcpp -Tp $(NMCPP_FLAGS) $(<) -O$(@) $(IDIRS) 

%.asmx: %.c
	$(SILENT_DEP)$(CROSS_COMPILE)gcc -E -MM $(<) -o$(@).dep
	$(SILENT_NMCPP)nmcpp -Tc99 $(NMCPP_FLAGS) $(<) -O$(@) $(IDIRS) 

%.o: %.asmx
	$(SILENT_ASM)asm $(C2ASM_FLAGS) $(<) -o$(@)

%.o: %.asm
	$(SILENT_DEP)$(CROSS_COMPILE)gcc -E -MM -xassembler-with-cpp $(<) -o$(@).dep
	$(SILENT_ASM)nmcc $(ASM_FLAGS) $(<) -o$(@)

$(TARGET).lib: $(OBJECTS)
	-$(SILENT_LIBRARIAN)libr -c $(@) $(^) > /dev/null

$(TARGET).abs: $(OBJECTS)
	-$(SILENT_LINKER)linker  $(BUILDER_FLAGS) -o$(@) $(^) $(LIBS) $(LIBDIR)

$(TARGET).dump: $(TARGET).abs
	-$(SILENT_NMDUMP)nmdump -f $(^) > $(@)

run: $(TARGET).abs
	$(MB7707)/bin/mb7707run -i -a$(MB7707_MAC)  $(TARGET).abs --send_file_name=in.ppm \
	--send_sect=.data_shared_src.bss --recv_file_name=out.ppm \
	--recv_sect=.data_shared_dst.bss --recv_size=0x1D51 \
	--send_size=0x1D51

clean:
	-$(SILENT_CLEAN)rm -f *.asmx; rm -f *.o; rm -f $(TARGET).abs $(TARGET).dump *.dep \
	*.ac *.map *~ *.abs *.lib
