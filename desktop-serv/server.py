from socket import socket, AF_INET, SOCK_DGRAM

sock = socket(AF_INET, SOCK_DGRAM)

sock.bind(("", 890))
try:
    while True:
      data, addr = sock.recvfrom(512)
      print "got " + str(data) + " from: " + str(addr)

except KeyboardInterrupt:
    sock.close()
