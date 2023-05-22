.PHONY: Common SocketServer SocketClient

all: Common SocketServer SocketClient

Common:
	$(MAKE) -C Common

SocketServer:
	$(MAKE) -C SocketServer

SocketClient:
	$(MAKE) -C SocketClient

clean:
	$(MAKE) -C Common clean
	$(MAKE) -C SocketServer clean
	$(MAKE) -C SocketClient clean