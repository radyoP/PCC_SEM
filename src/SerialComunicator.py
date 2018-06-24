import zmq
import time
import serial

def run():
    ser = serial.Serial('/dev/ttyUSB0', 9600)
    print("python started")

    context = zmq.Context()
    socket = context.socket(zmq.REQ)
    socket.connect("tcp://localhost:5555")

    while True:
        line = ser.readline()
        print(f"Arduino send: {line}")
        socket.send(line.encode())
        message = socket.recv()
        ser.write(message.encode())
        print(f'reply: {message}')
        time.sleep(1)

if __name__ == '__main__':
    run()