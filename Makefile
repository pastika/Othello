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

#OBJS       = $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(wildcard $(SDIR)/*.cpp))

PROGRAMS = othello server client

all: objdir $(PROGRAMS)

objdir:
	mkdir -p $(ODIR)

$(ODIR)/%.o : $(SDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

othello: $(ODIR)/othelloArbiter.o $(ODIR)/othelloPlayerLOM.o $(ODIR)/othelloPlayerRandom.o $(ODIR)/othello.o
	$(LD) $^ $(LIBS) -o $@

server: $(ODIR)/othelloPlayerLOM.o $(ODIR)/othelloArbiter.o $(ODIR)/othelloServer.o
	$(LD) $^ $(LIBS) -o $@

client: $(ODIR)/othelloArbiterClient.o $(ODIR)/othelloPlayerRandom.o $(ODIR)/othelloClient.o
	$(LD) $^ $(LIBS) -o $@

clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.d $(PROGRAMS) core 

-include $(ODIR)/*.d
