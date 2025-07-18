EXE = main.exe

CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lncurses

SRCDIR_1 = 1_size
SRCDIR_2 = 2_menue
SRCDIR_3 = 3_game

OBJECTS = main.o \
          define.o \
          $(SRCDIR_1)/set_size.o \
          $(SRCDIR_2)/handle_menue.o \
          $(SRCDIR_2)/observe_connection.o \
          $(SRCDIR_2)/screen_connect.o \
          $(SRCDIR_2)/screen_guest.o \
          $(SRCDIR_2)/screen_help.o \
          $(SRCDIR_2)/screen_host.o \
          $(SRCDIR_2)/screen_opponent.o \
          $(SRCDIR_2)/screen_top.o \
          $(SRCDIR_3)/game_algo.o \
          $(SRCDIR_3)/game_init_dis.o \
          $(SRCDIR_3)/game_judge.o \
          $(SRCDIR_3)/game_run.o \
          $(SRCDIR_3)/game_serch_placeable.o \
          $(SRCDIR_3)/game_tips.o \
          $(SRCDIR_3)/run_function.o \
          $(SRCDIR_3)/start_game.o

$(EXE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJECTS) $(LIBS)


main.o: main.c
	$(CC) $(CFLAGS) -c main.c

define.o: define.c
	$(CC) $(CFLAGS) -c define.c

$(SRCDIR_1)/set_size.o: $(SRCDIR_1)/set_size.c
	$(CC) $(CFLAGS) -c $(SRCDIR_1)/set_size.c -o $(SRCDIR_1)/set_size.o

$(SRCDIR_2)/handle_menue.o: $(SRCDIR_2)/handle_menue.c
	$(CC) $(CFLAGS) -c $(SRCDIR_2)/handle_menue.c -o $(SRCDIR_2)/handle_menue.o

$(SRCDIR_2)/observe_connection.o: $(SRCDIR_2)/observe_connection.c
	$(CC) $(CFLAGS) -c $(SRCDIR_2)/observe_connection.c -o $(SRCDIR_2)/observe_connection.o

$(SRCDIR_2)/screen_connect.o: $(SRCDIR_2)/screen_connect.c
	$(CC) $(CFLAGS) -c $(SRCDIR_2)/screen_connect.c -o $(SRCDIR_2)/screen_connect.o

$(SRCDIR_2)/screen_guest.o: $(SRCDIR_2)/screen_guest.c
	$(CC) $(CFLAGS) -c $(SRCDIR_2)/screen_guest.c -o $(SRCDIR_2)/screen_guest.o

$(SRCDIR_2)/screen_help.o: $(SRCDIR_2)/screen_help.c
	$(CC) $(CFLAGS) -c $(SRCDIR_2)/screen_help.c -o $(SRCDIR_2)/screen_help.o

$(SRCDIR_2)/screen_host.o: $(SRCDIR_2)/screen_host.c
	$(CC) $(CFLAGS) -c $(SRCDIR_2)/screen_host.c -o $(SRCDIR_2)/screen_host.o

$(SRCDIR_2)/screen_opponent.o: $(SRCDIR_2)/screen_opponent.c
	$(CC) $(CFLAGS) -c $(SRCDIR_2)/screen_opponent.c -o $(SRCDIR_2)/screen_opponent.o

$(SRCDIR_2)/screen_top.o: $(SRCDIR_2)/screen_top.c
	$(CC) $(CFLAGS) -c $(SRCDIR_2)/screen_top.c -o $(SRCDIR_2)/screen_top.o

$(SRCDIR_3)/game_algo.o: $(SRCDIR_3)/game_algo.c
	$(CC) $(CFLAGS) -c $(SRCDIR_3)/game_algo.c -o $(SRCDIR_3)/game_algo.o

$(SRCDIR_3)/game_init_dis.o: $(SRCDIR_3)/game_init_dis.c
	$(CC) $(CFLAGS) -c $(SRCDIR_3)/game_init_dis.c -o $(SRCDIR_3)/game_init_dis.o

$(SRCDIR_3)/game_judge.o: $(SRCDIR_3)/game_judge.c
	$(CC) $(CFLAGS) -c $(SRCDIR_3)/game_judge.c -o $(SRCDIR_3)/game_judge.o

$(SRCDIR_3)/game_run.o: $(SRCDIR_3)/game_run.c
	$(CC) $(CFLAGS) -c $(SRCDIR_3)/game_run.c -o $(SRCDIR_3)/game_run.o

$(SRCDIR_3)/game_serch_placeable.o: $(SRCDIR_3)/game_serch_placeable.c
	$(CC) $(CFLAGS) -c $(SRCDIR_3)/game_serch_placeable.c -o $(SRCDIR_3)/game_serch_placeable.o

$(SRCDIR_3)/game_tips.o: $(SRCDIR_3)/game_tips.c
	$(CC) $(CFLAGS) -c $(SRCDIR_3)/game_tips.c -o $(SRCDIR_3)/game_tips.o

$(SRCDIR_3)/run_function.o: $(SRCDIR_3)/run_function.c
	$(CC) $(CFLAGS) -c $(SRCDIR_3)/run_function.c -o $(SRCDIR_3)/run_function.o

$(SRCDIR_3)/start_game.o: $(SRCDIR_3)/start_game.c
	$(CC) $(CFLAGS) -c $(SRCDIR_3)/start_game.c -o $(SRCDIR_3)/start_game.o
clean:
	rm -f $(EXE) $(OBJECTS)
	rm -f  set_size.o \
          handle_menue.o \
          observe_connection.o \
          screen_connect.o \
          screen_guest.o \
          screen_help.o \
          screen_host.o \
          screen_opponent.o \
          screen_top.o \
          game_algo.o \
          game_init_dis.o \
          game_judge.o \
          game_run.o \
          game_serch_placeable.o \
          game_tips.o \
          run_function.o \
          start_game.o
