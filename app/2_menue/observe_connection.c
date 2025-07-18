// function
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>


#include "observe_connection.h"
#include "../define.h"
#include "../boolean.h"




boolean observe_connection(int mode) {
    int sock_fd = -1;
    struct sockaddr_in serv_addr;
    boolean success = false;


    if (mode == HOST) {
        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (sock_fd < 0) {
            return false;
        }

        int opt = 1;
        setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(PORT);

        if (bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
            close(sock_fd);
            return false;
        }
        if (listen(sock_fd, 1) < 0) {
            close(sock_fd);
            return false;
        }

        refresh();

        fd_set read_fds;
        struct timeval timeout;

        timeout.tv_sec = TIMEOUT;
        timeout.tv_usec = 0;

        FD_ZERO(&read_fds);
        FD_SET(sock_fd, &read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        int acv = select(sock_fd + 1, &read_fds, NULL, NULL, &timeout);

        if (acv > 0 && FD_ISSET(sock_fd, &read_fds)) {
            int conn_fd = accept(sock_fd, NULL, NULL);
            if (conn_fd > 0) {
                success = true;
                connection_fd = conn_fd;
            }
        }

        if (acv > 0 && FD_ISSET(STDIN_FILENO, &read_fds)) {
            if (getch() == ESCAPE) {
                return false;
            }
        }

    } else if (mode == GUEST) {
        while(true){
            char target_ipaddres[40] = {0};
            int ch;
            size_t i = 0;
            keypad(stdscr, TRUE);
            move(center_y+1-3, center_x-18);
            printw(">>");
            refresh();
            curs_set(1);

            while (i < sizeof(target_ipaddres) - 2) {
                ch = getch();
                if (ch == ESCAPE) { // escape
                    return false;
                } else if (ch == ENTER) { // Enter
                    break;
                } else if (ch == KEY_BACKSPACE || ch == BACKSPACE) { // Backspace
                    if (i > 0) {
                        int y, x;
                        i--;
                        getyx(stdscr, y, x);
                        move(y, x - 1);
                        delch();
                    }
                } else if (ch >= SPACE && ch <= TILDE) {
                    target_ipaddres[i++] = ch;
                    addch(ch);
                }
            }
            target_ipaddres[i] = '\0';
            move(3, 1);
            clrtoeol();
            mvprintw(3, 1, "　　　　接続中...");
            refresh();
            sock_fd = socket(AF_INET, SOCK_STREAM, 0);
            if (sock_fd < 0) {
                return false;
            }

            memset(&serv_addr, 0, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;
            serv_addr.sin_port = htons(PORT);

            if (inet_pton(AF_INET, target_ipaddres, &serv_addr.sin_addr) <= 0) {

                success = false;
            } else if (connect(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
                move(3, 1);
                clrtoeol();
                mvprintw(3, 1, "　　　　接続エラー: ホストが見つからないか拒否されました。");
                refresh();
                ch = getch();
                success = false;
                close(sock_fd);
                move(center_y+1-3, center_x-18);
                clrtoeol();
            } else {

                success = true;
                connection_fd = sock_fd;
                break;
            }

        }
    }

    if (mode == HOST) {
        // host
        if (sock_fd != -1) {
            close(sock_fd);
        }
    } else if (mode == GUEST) {
        // guest
    }
    return success;
}
