import socket

host = "www.ctralie.com"
path = "ctralie_cv.pdf"
port = 80
filename = "out.pdf"


## Step 1: Get address info for host
sock = None
addr = None
for option in socket.getaddrinfo(host, port, socket.AF_UNSPEC, socket.SOCK_STREAM):
    af, socktype, proto, canonname, addr = option
    ## Step 1a: Try to open socket
    try:
        sock = socket.socket(af, socktype, proto)
    except OSError as msg:
        sock = None
        continue
    ## Step 1b: Try to connect onto this socket
    try:
        sock.connect(addr)
    except OSError as msg:
        sock.close()
        sock = None
        continue
    break

if not socket: # If the socket is None, we didn't find a configuration that worked
    raise Exception("Was not able to get the socket to work!")

## Step 2: Send HTTP Request
msg = f"GET {path} HTTP/1.0\r\nHost: {host}\r\n\r\n"
msg = msg.encode("ascii")
sock.sendall(msg)

## Step 3: Get HTTP Response
BUFSIZE = 1024
ret = sock.recv(BUFSIZE)
print(len(ret))
resp = ret
while len(ret) > 0:
    ret = sock.recv(BUFSIZE)
    print(len(ret))
    resp += ret

## Step 4: Find beginning of HTTP response body, and write
## bytes to a chosen file
idx = resp.index(b"\r\n\r\n") + 4 # Go to the end of the header
with open(filename, "wb") as fout:
    fout.write(resp[idx:])
    fout.close()

