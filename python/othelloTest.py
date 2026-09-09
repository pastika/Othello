import OthelloBoard
import socket

def main():
    board = OthelloBoard.OthelloBoard()

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    sock.connect(("localhost", 3490))

    data = sock.recv(1024).decode("utf-8")
    print(data)

    sock.sendall(b"2")
    
    data = sock.recv(1024).decode("utf-8")
    print(data)

    sock.sendall(b"2")

    data = sock.recv(1024).decode("utf-8")
    print(data)

    sock.sendall(b"1")

    #while True:
    for i in range(32):
        stop = False
        data = sock.recv(1024).decode("utf-8")

        data_split = data.split(";")
        message = data_split[0].strip()
        player = data_split[1].strip()
        board_package = " ; ".join(data_split[2:]).strip()

        if "winner" in message:
            winner = int(data.split(";")[0].split(":")[1].strip())
            print()
            print("winner: %s"%board.playerToChar(winner))
            stop = True
        elif "play" in message:
            pass
        else:
            print(data)

        board.constructBoard(board_package)
        board.availableMoves(int(player))
        print()
        board.print()
        print()
            
        if stop:
            break

        # play at random
        moves = board.moves_
        if len(moves):
            move = moves[-1]
            print(f"move: {move[0]} {move[1]}")
            sock.sendall(f"{move[0]} {move[1]}".encode("utf-8"))
        else:
            sock.sendall(b"pass")
        
            
if __name__ == "__main__":
    main()
