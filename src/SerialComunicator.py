import zmq
import time

def run():
    print("python started")

    context = zmq.Context()
    socket = context.socket(zmq.REQ)
    socket.connect("tcp://localhost:5555")
    socket.send(b"42")
    message = socket.recv()
    print(f'reply: {message}')
    for i in range(10, 20):
        socket.connect("tcp://localhost:5555")
        socket.send(str(i).encode())
        message = socket.recv()
        print(f'reply: {message}')
        time.sleep(1)

if __name__ == '__main__':
    run()