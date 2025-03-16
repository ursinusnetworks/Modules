import socket
import struct # Used for binary data
import threading # For multithreaded

## Step 1: Bind server to my address and listen
PORT = 60001
BACKLOG = 10
sock = None
for res in socket.getaddrinfo(None, PORT, socket.AF_UNSPEC, socket.SOCK_STREAM, flags=socket.AI_PASSIVE):
    af, socktype, proto, canonname, sa = res
    try:
        sock = socket.socket(af, socktype, proto)
    except OSError as msg:
        sock = None
        continue
    try:
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.bind(sa)
        sock.listen(BACKLOG)
    except Exception as msg:
        sock.close()
        sock = None
        continue
    break

if not sock:
    raise Exception("Wasn't able to make a socket!")


## Step 2: Define client handler
counter = 0 # Increment every time I sent 
lock = threading.Lock()

def service_client(clientsock, lock):
    global counter
    header = clientsock.recv(7)
    with lock:
        counter += 1
    (len_name, len_msg, magic) = struct.unpack("!HIB", header)
    name = clientsock.recv(len_name)
    msg = clientsock.recv(len_msg)
    print(f"Received name {name}, msg {msg}, magic {magic}")
    clientsock.close()

## Step 3: Setup accept loop
while True:
    (clientsock, clientaddr) = sock.accept()
    t = threading.Thread(target=service_client, args=(clientsock, lock))
    t.start()
