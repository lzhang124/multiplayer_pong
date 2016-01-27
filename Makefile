ifeq ($(OS),Windows_NT)
COMMAND = mkdir
else
COMMAND = mkdir -p
endif

all :
	$(COMMAND) build
	cd Multiplayer\ Pong; make
	cd Server; make
