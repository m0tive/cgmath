NAME := MCG
BUILD := debug
COMPILER := g++
#DOXYGEN := Doxyfile

FLAGS := -Wall
DEFINES := -DUNIX -DLINUX

#INCDIR := 
SRCDIR := .
OUTDIR := .

LIBS := 

#INCLUDE := -I$(INCDIR)

ifeq "$(BUILD)" "debug"

FLAGS += -g
DEFINES += -D_DEBUG
LIBS +=
OBJDIR := obj/Debug
TARGET := lib$(NAME).a

else

FLAGS +=
DEFINES += 
LIBS +=
OBJDIR := obj/Release
TARGET := lib$(NAME).a

endif

$(shell if ! [ -d $(OUTDIR) ] ; then mkdir -p $(OUTDIR); fi)
$(shell if ! [ -d $(OBJDIR) ] ; then mkdir -p $(OBJDIR); fi)
$(shell if ! [ -d .kate ] ; then mkdir .kate; fi)

FILES := $(shell ls *.cpp)

OBJECTS:= $(addprefix $(OBJDIR)/, $(FILES:.cpp=.o))

## create all
all : $(OUTDIR)/$(TARGET)

## Archive the object files
$(OUTDIR)/$(TARGET): $(OBJECTS)
	ar rcs $(OUTDIR)/$(TARGET) $(OBJECTS)

## Compile the object files
$(OBJECTS): $(OBJDIR)/%.o: %.cpp
	$(COMPILER) -c $(FLAGS) $(DEFINES) $< -o $@
	
## Remove extra stuff
clean :
	rm -f $(OUTDIR)/$(TARGET)
	rm -f $(OBJECTS)
	
kate_clean :
	mv -f ./*~ .kate/.

ifdef DOXYGEN

doxygen :
	doxygen $(DOXYGEN)
	
endif	
