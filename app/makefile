EXE = main.exe


CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lncurses


SRCDIR_1 = 1_size
SRCDIR_2 = 2_menue
SRCDIR_3 = 3_game

SOURCES = main.o \
		   $(SRCDIR_1)/set_size.o \
		   $(SRCDIR_2)/handle_menue.o \
		   $(SRCDIR_2)/observ_connection.o \
		   $(SRCDIR_2)/screen_connect.o \
		   $(SRCDIR_2)/screen_guest.o \
		   $(SRCDIR_2)/screen_help.o \
		   $(SRCDIR_2)/screen_host.o \
		   $(SRCDIR_2)/screen_opponent.o \
		   $(SRCDIR_2)/screen_top.o \
		   $(SRCDIR_3)/game_bind_sp.o \
		   $(SRCDIR_3)/game_judge.o \
		   $(SRCDIR_3)/game_run.o \
		   $(SRCDIR_3)/run_function.o \
		   $(SRCDIR_3)/start_game.o

main.exe : $(SOURCES)
		$(CC) $(CFLAGS) -o $(EXE) $(SOURCES) $(LIBS)

main.o:main.c
		$(CC) $(CFLAGS) -c main.c

$(SRCDIR_1)/set_size.o:$(SRCDIR_1)/set_size.c
		$(CC) $(CFLAGS) -c $(SRCDIR_1)/set_size.c

$(SRCDIR_2)/handle_menue.o:$(SRCDIR_2)/handle_menue.c
		$(CC) $(CFLAGS) -c $(SRCDIR_2)/handle_menue.c

$(SRCDIR_2)/observ_connection.o:$(SRCDIR_2)/observ_connection.c
		$(CC) $(CFLAGS) -c $(SRCDIR_2)/observ_connection.c

$(SRCDIR_2)/screen_connect.o:$(SRCDIR_2)/screen_connect.c
		$(CC) $(CFLAGS) -c $(SRCDIR_2)/screen_connect.c

$(SRCDIR_2)/screen_guest.o:$(SRCDIR_2)/screen_guest.c
		$(CC) $(CFLAGS) -c $(SRCDIR_2)/screen_guest.c

$(SRCDIR_2)/screen_help.o:$(SRCDIR_2)/screen_help.c
		$(CC) $(CFLAGS) -c $(SRCDIR_2)/screen_help.c

$(SRCDIR_2)/screen_host.o:$(SRCDIR_2)/screen_host.c
		$(CC) $(CFLAGS) -c $(SRCDIR_2)/screen_host.c

$(SRCDIR_2)/screen_opponent.o:$(SRCDIR_2)/screen_opponent.c
		$(CC) $(CFLAGS) -c $(SRCDIR_2)/screen_opponent.c

$(SRCDIR_2)/screen_top.o:$(SRCDIR_2)/screen_top.c
		$(CC) $(CFLAGS) -c $(SRCDIR_2)/screen_top.c

$(SRCDIR_3)/game_bind_sp.o:$(SRCDIR_3)/game_bind_sp.c
		$(CC) $(CFLAGS) -c $(SRCDIR_3)/game_bind_sp.c

$(SRCDIR_3)/game_judge.o:$(SRCDIR_3)/game_judge.c
		$(CC) $(CFLAGS) -c $(SRCDIR_3)/game_judge.c

$(SRCDIR_3)/game_run.o:$(SRCDIR_3)/game_run.c
		$(CC) $(CFLAGS) -c $(SRCDIR_3)/game_run.c

$(SRCDIR_3)/run_function.o:$(SRCDIR_3)/run_function.c
		$(CC) $(CFLAGS) -c $(SRCDIR_3)/run_function.c

$(SRCDIR_3)/start_game.o:$(SRCDIR_3)/start_game.c
		$(CC) $(CFLAGS) -c $(SRCDIR_3)/start_game.c

clean:
		rm -f $(EXE) $(SOURCES) *.o
		rm -f $(SRCDIR_1)/*.o $(SRCDIR_2)/*.o $(SRCDIR_3)/*.o
		rm -f $(SRCDIR_1)/*.exe $(SRCDIR_2)/*.exe $(SRCDIR_3)/*.exe
