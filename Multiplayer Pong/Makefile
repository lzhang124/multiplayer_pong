all : pong

CFLAGS = -Wno-deprecated

ifeq ($(OS),Windows_NT)
LDFLAGS = -lopengl32 -lglu32 -lglut32
else
LDFLAGS = -framework OpenGL -framework GLUT
endif

pong : main.c pong.c client.c draw.c paddle.c ball.c
	gcc main.c pong.c client.c draw.c paddle.c ball.c -o ../build/pong $(CFLAGS) $(LDFLAGS)
