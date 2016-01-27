ifeq ($(OS),Windows_NT)
COMMAND = dir
else
COMMAND = cd
endif

all :
	mkdir -p build
	$(COMMAND) Multiplayer\ Pong; make
	$(COMMAND) Server; make
