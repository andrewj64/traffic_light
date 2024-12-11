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
INC        = $(SDIR) $(LDIR)
INC_PARAMS = $(foreach d, $(INC), -I$d)
DEPFLAGS   = -MT $@ -MMD -MP -MF $(DDIR)/$*.Td
CFLAGS     = -Wall

#The full command for compilation
CC       = gcc $(CFLAGS) $(INC_PARAMS) $(DEPFLAGS)
CL       = gcc $(CFLAGS)
POSTCC   = @mv -f $(DDIR)/$*.Td $(DDIR)/$*.d && touch $@

#Default make target: setup the environment, build the program, build and run tests
.PHONY: all
all: | toolchain $(PNAME) test_suite

#List all sources to be included in the project (except main.c)
_SRCS = lights.c

#Derived variable SRCS used by dependency management
SRCS  = main.c $(_SRCS)
SRCST = test_suite.c

#Derived variables POBJ/TOBJ lists dependencies for the output binaries
POBJ = $(ODIR)/main.o $(patsubst %.c, $(ODIR)/%.o, $(_SRCS))
TOBJ = $(ODIR)/test_suite.o $(patsubst %.c, $(ODIR)/%.o, $(_SRCS)) #$(ODIR)/test_suite.o

#Program link step
$(BDIR)/$(PNAME): $(POBJ)
	$(CL) -o $@ $^ $(LINKFLAGS)
#link tests
$(BDIR)/test_suite: $(TOBJ)
	$(CL) -o $@ $^ $(LINKFLAGS)

#All compilation units in the project
$(ODIR)/%.o: $(SDIR)/%.c $(DDIR)/%.d
	$(CC) -c -o $@ $<
	$(POSTCC)
#tests
$(ODIR)/%.o: $(TDIR)/%.c $(DDIR)/%.d
	$(CC) -c -o $@ $<
	$(POSTCC)


#Standard build targets
.PHONY: clean
clean:
	rm -rf $(DDIR) $(ODIR) $(BDIR)

.PHONY: toolchain pmain $(PNAME) ptest test_suite
toolchain: | $(BDIR) $(ODIR) $(DDIR)
pmain: $(BDIR)/$(PNAME) 
ptest: $(BDIR)/test_suite
$(PNAME): | toolchain pmain
test_suite: | toolchain ptest

#run tests
.PHONY: test
test: test_suite ptest
	@echo "====================================="
	@echo "Running Test Suite"
	@echo "====================================="
	$(BDIR)/test_suite

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
include $(wildcard $(patsubst %,$(TDIR)/%.d,$(basename $(SRCST))))