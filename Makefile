SHELL = /bin/sh
NAME ?= libCGMath

srcdir = .

cppdir ?= $(srcdir)/src
hppdir ?= $(srcdir)/include/CGM
objdir ?= $(srcdir)/obj
outdir ?= $(srcdir)/lib


SRC := $(notdir $(wildcard $(cppdir)/*.cpp))
OBJ := $(SRC:cpp=o)

CPPFLAGS += -DUNIX -DLINUX

CXXFLAGS += -I$(hppdir)
CXXFLAGS += -Wall

DEBUGFLAGS = -g -D_DEBUG
RELEASEFLAGS = -DNDEBUG


default: debug
	$(info Choose a build: [ debug, release ])
	@exit 0


debug: $(outdir) $(objdir)/debug $(outdir)/$(NAME)-debug.a

%-debug.a : $(addprefix $(objdir)/debug/, $(OBJ))
	$(AR) $(ARFLAGS) $@ $^

$(objdir)/debug/%.o : $(cppdir)/%.cpp $(wildcard $(hppdir)/*.hpp)
	@echo dep $(addprefix $(hppdir)/, $(shell cat $< | grep -o [^\"]*hpp))
	$(CXX) -c $(DEBUGFLAGS) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<


all: release check

release: $(outdir) $(objdir)/release $(outdir)/$(NAME).a

%$(NAME).a : $(addprefix $(objdir)/release/, $(OBJ))
	$(AR) $(ARFLAGS) $@ $^

$(objdir)/release/%.o : $(cppdir)/%.cpp
	$(CXX) -c $(RELEASEFLAGS) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<


$(objdir)/debug : $(objdir)
	-mkdir $@

$(objdir)/release : $(objdir)
	-mkdir $@

$(objdir) :
	-mkdir $@

$(outdir) :
	-mkdir $@

.PRECIOUS : $(objdir)/debug/%.o $(objdir)/release/%.o

TAGS:
	ctags -VR --languages=C++ $(cppdir) $(hppdir)

clean:
	$(RM) -v $(outdir)/$(NAME).a $(outdir)/$(NAME)-debug.a $(addprefix $(objdir)/debug/, $(OBJ)) $(addprefix $(objdir)/release/, $(OBJ))

check:
	@echo run unit test

.PONEY : default debug release clean TAGS

