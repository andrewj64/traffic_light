#Output program name to make this Makefile more reusable
PNAME = traffic_light

#Project Tree Structure
LDIR = lib
SDIR = src
ODIR = obj
BDIR = bin
DDIR = dep
TDIR = test

#Compiler flag variables
INC        = $(SDIR)
INC_PARAMS = $(foreach d, $(INC), -I$d)
DEPFLAGS   = -MT $@ -MMD -MP -MF $(DDIR)/$*.Td
CFLAGS     = -Wall

#The full command for compilation
CC       = gcc $(CFLAGS) $(INC_PARAMS) $(DEPFLAGS)
CL       = gcc $(CFLAGS)
POSTCC   = @mv -f $(DDIR)/$*.Td $(DDIR)/$*.d && touch $@

#Default make target: setup the environment, build the program, build and run tests
.PHONY: all
all: | toolchain $(PNAME)

#List all sources to be included in the project (except main.c)
_SRCS = lights.c

#Derived variable SRCS used by dependency management
SRCS  = main.c $(_SRCS)

#Derived variables POBJ/TOBJ lists dependencies for the output binaries
POBJ = $(ODIR)/main.o $(patsubst %.c, $(ODIR)/%.o, $(_SRCS))

#Program link step
$(BDIR)/$(PNAME): $(POBJ)
	$(CL) -o $@ $^ $(LINKFLAGS)

#All compilation units in the project
$(ODIR)/%.o: $(SDIR)/%.c $(DDIR)/%.d
	$(CC) -c -o $@ $<
	$(POSTCC)

#Standard build targets
.PHONY: clean
clean:
	rm -rf $(DDIR) $(ODIR) $(BDIR)

.PHONY: toolchain pmain $(PNAME)
toolchain: | $(BDIR) $(ODIR) $(DDIR)
pmain: $(BDIR)/$(PNAME)
$(PNAME): | toolchain pmain

$(DDIR):
	@mkdir $(DDIR)

$(ODIR):
	@mkdir $(ODIR)

$(BDIR):
	@mkdir $(BDIR)

#Dependency management
$(DDIR)/%.d: ;
.PRECIOUS: $(DDIR)/%.d

include $(wildcard $(patsubst %,$(DDIR)/%.d,$(basename $(SRCS))))