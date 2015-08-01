#include <set>
#include <utility>

#ifndef OTHELLOPLAYER_h
#define OTHELLOPLAYER_h

class OthelloPlayer
{
private:
    virtual void returnPlay(const unsigned char ** const, const std::set<std::pair<int, int>>&, int&, int&) = 0;

public:
    inline void operator()(const unsigned char ** const board, const std::set<std::pair<int, int>>& plays, int& x, int& y)
    {
        returnPlay(board, plays, x, y);
    }
};

#endif
