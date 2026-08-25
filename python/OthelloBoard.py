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
        
        self.moves_ = []
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

    def availableMoves(self, player: int):
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
                                if self.board_[xp, yp] == 0 or self.board_[xp, yp] == player:
                                    continue
                                for k in range(nmMax):
                                    if self.board_[xp + k*dirX, yp + k*dirY] == player:
                                        moves.append([i, j])
                                        skip = True
                                        break
                            except IndexError:
                                pass
                        if skip: break
                    if skip: break

        return np.array(moves)

    def play(self, player, x, y) -> bool:
        if not self.onBoard(x, y) or self.board_[x, y] != 0:
            return False

        moves = self.availableMoves(player)
        if not np.array([x,y]) in moves:
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
                
                
if __name__ == "__main__":
    # test code 
    board = OthelloBoard()

    print(board.board_)
    print(board.constructBoard(board.packageBoard()))
    print(board.board_)

    print(board.winner())
    print(board.availableMoves(1))
    print(board.play(1, 2, 3))
    print(board.board_)
    print(board.availableMoves(2))
    print(board.play(2, 2, 2))
    print(board.board_)

    
