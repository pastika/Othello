import numpy as np

class OthelloBoard:
    def __init__(self, N: int = 8, M: int = 8):
        self.N_ = N
        self.M_ = M
        self.board_ = np.zeros([N, M], dtype=int)

        self.board_[int(N/2) - 1, int(M/2) - 1] = 2
        self.board_[int(N/2)    , int(M/2) - 1] = 1
        self.board_[int(N/2) - 1, int(M/2)    ] = 1
        self.board_[int(N/2)    , int(M/2)    ] = 2
        
        self.moves_ = np.array([], dtype=int)
        self.lastPlayer_ = 0

    def onBoard(self, x, y) -> bool:
        return x >= 0 and y >= 0 and x < self.N_ and y < self.M_
        
    def packageBoard(self) -> str:
        return f"{self.N_} {self.M_} " + "".join(self.board_.flatten().astype(str)) + f" ; {self.lastPlayer_}"

    def constructBoard(self, boardPackage: str) -> bool:
        try:
            splitPack = boardPackage.split(";")
            self.lastPlayer_ = int(splitPack[1])
            splitPack = splitPack[0].strip().split()
            n = int(splitPack[0])
            m = int(splitPack[1])
            if(not(n == self.N_) or not(m == self.M_)):
                return False
            boardList = [int(c) for c in splitPack[2].strip()]
            self.board_ = np.array(boardList).reshape([self.N_, self.M_])
        except:
            return False
        return True

    def winner(self) -> int:
        counts = np.vstack(np.unique(self.board_, return_counts=True)).transpose()
        counts = counts[counts[:,0] > 0]
        counts = counts[counts[:,1].argsort(descending=True)]
        if counts[0,1] > counts[1,1]:
            return counts[0,0]
        else:
            return 0

    def availableMoves(self, player: int) -> int:
        moves = []
        nmMax = max(self.N_, self.M_)
        for i in range(self.N_):
            for j in range(self.M_):
                # skip any position which already has a piece 
                if self.board_[i,j]:
                    continue
                # scan for pieces of your player type
                
                dirSet = [-1, 0 ,1]
                skip = False
                for dirX in dirSet:
                    for dirY in dirSet:
                        if dirX or dirY:
                            xp = i + dirX
                            yp = j + dirY
                            try:
                                if not self.onBoard(xp, yp) or self.board_[xp, yp] == 0 or self.board_[xp, yp] == player:
                                    continue
                                for k in range(1, nmMax):
                                    if not self.onBoard(xp + k*dirX, yp + k*dirY) or self.board_[xp + k*dirX, yp + k*dirY] == 0:
                                        break
                                    elif self.board_[xp + k*dirX, yp + k*dirY] == player:
                                        print(i, j, xp, yp, dirX, dirY, k)
                                        moves.append([i, j])
                                        skip = True
                                        break
                            except IndexError:
                                pass
                        if skip: break
                    if skip: break

        self.moves_ = np.array(moves, dtype=int)
        return len(self.moves_)

    def play(self, player, x, y) -> bool:
        if not self.onBoard(x, y) or self.board_[x, y] != 0:
            return False

        if not np.array([x,y]) in self.moves_:
            return False
            
        dirSet = [-1, 0 ,1]
        for dirX in dirSet:
            for dirY in dirSet:
                if dirX or dirY:
                    xp = x + dirX
                    yp = y + dirY
                    direction = 1
                    try:
                        while xp != x or yp != y:
                            if self.board_[xp, yp] == 0:
                                break
                            if self.board_[xp, yp] == player:
                                direction = -1
                            if direction == 1:
                                xp += dirX
                                yp += dirY
                            else:
                                xp -= dirX
                                yp -= dirY
                                self.board_[xp, yp] = player
                    except IndexError:
                        pass
                    
        #self.board_[x, y] = player

        return True

    def print(self):
        print(self.constructDisplayString())

    def constructDisplayString(self) -> str:
        boardLocal = np.zeros([self.N_, self.M_], dtype=int)
        if len(self.moves_):
            boardLocal[self.moves_[:,0], self.moves_[:,1]] = 255
        boardLocal += self.board_
        
        displayStr  = "    " + "".join(["%2d"%i for i in range(self.M_)]) + "\n"
        displayStr += "   " + "-"*(2*self.M_+3) + "\n"
        for j, line in enumerate(boardLocal):
            displayStr += "%2d"%j + " |"
            displayStr += "".join(["%2s"%self.playerToChar(p) for p in line])
            displayStr += " |\n"

        displayStr += "   " + "-"*(2*self.M_+3)
                
        return displayStr

    def playerToChar(self, player) -> str:
        match player:
            case 0:   return ' '
            case 1:   return ' \x1b[31mX\x1b[0m'
            case 2:   return ' \x1b[34mO\x1b[0m'
            case 255: return ' \x1b[32m+\x1b[0m'
            case _:   return '-'
            
            
if __name__ == "__main__":
    # test code 
    board = OthelloBoard()

    board.constructBoard(board.packageBoard())
    
    board.availableMoves(1)
    board.print()
    board.play(1, 2, 3)
    board.availableMoves(2)
    board.print() 
    board.play(2, 2, 2)
    board.availableMoves(1)
    board.print()
    board.play(1, 3, 2)
    board.availableMoves(2)
    board.print()
    board.play(2, 4, 2)
    board.availableMoves(1)
    board.print()
   
    for i in range(10000):
        board.availableMoves(1)
