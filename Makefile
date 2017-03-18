IDIR       = .
ODIR       = obj
SDIR       = .

CXX        = g++

CXXFLAGS  += -I. -std=c++11
## Optimization flag
CXXFLAGS += -g #-O3
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
	$(LD) $^ $(LIBS) -o $@

server:
	g++ -g --std=c++11 othelloPlayerLOM.cpp othelloArbiter.cpp serverTest.cpp -o server

client:
	g++ -g --std=c++11 clientTest.cpp -o client

clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.d $(PROGRAMS) core 

-include $(ODIR)/*.d
