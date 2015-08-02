IDIR       = .
ODIR       = obj
SDIR       = .

CXX        = g++

CXXFLAGS  += -I. -std=c++0x
## Optimization flag
CXXFLAGS += -O3
## Enable the maximun warning
#CXXFLAGS += -Wall -Wextra -Weffc++ -g

CXXDEPFLAGS = -MMD -MP

LD         = g++
LDFLAGS    =

OBJS       = $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(wildcard $(SDIR)/*.cpp))

PROGRAMS = othello

all: objdir $(PROGRAMS)

objdir:
	mkdir -p $(ODIR)

$(ODIR)/%.o : $(SDIR)/%.C
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(SDIR)/%.cc
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(SDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

othello: $(OBJS)
	$(LD) $^ $(LIBS) $(MT2LIB) -o $@

clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.d $(PROGRAMS) core 

-include $(ODIR)/*.d
