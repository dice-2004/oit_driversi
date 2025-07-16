// module

#include <ncurses.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "screen_host.h"
#include "observe_connection.h"
#include "../boolean.h"
#include "../define.h"

void display_host(void);

int screen_host(void){
    display_host();

    boolean result =observe_connection(HOST);
    curs_set(0);
    clear();
    if (result) {
        mvprintw(center_y, center_x-9, "接続に成功しました！");
        refresh();
        sleep(3);
        clear();
        mode = HOST;
        return EXIT;
    } else {
        mvprintw(center_y, center_x-9, "接続に失敗しました。");
        refresh();
        sleep(3);
        clear();
        return TOP;
    }
}

void display_host() {
    clear();
    attron(A_BOLD);
    attron(COLOR_PAIR(4));
    mvprintw(29, 135-62, "相手のプレイヤーは「接続する」を選択しホストIDを入力して下さい");
    attroff(COLOR_PAIR(4));
    attroff(A_BOLD);
    struct ifaddrs *ifaddr;
    struct ifaddrs *ifa;
    char host_id[100];

    if(getifaddrs(&ifaddr) == -1) {
        beep();
        mvprintw(30, 135-28, "ホストIDの取得に失敗しました。");
        refresh();
        timeout(1);
        getch();
        return;
    }
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        // ipv4,up, not loopback

        if (ifa->ifa_addr != NULL && ifa->ifa_addr->sa_family == AF_INET &&(ifa->ifa_flags & IFF_UP) && !(ifa->ifa_flags & IFF_LOOPBACK)) {

            struct sockaddr_in *addr = (struct sockaddr_in *)ifa->ifa_addr;
            inet_ntop(AF_INET, &addr->sin_addr, host_id, sizeof(host_id));
            if(strncmp(host_id, "169.254.",8) == 0 ){
                continue;
            }
            attron(COLOR_PAIR(5));
            attron(A_BOLD);
            mvprintw(center_y, center_x-10, "　ホストID: %s　", host_id);
            attroff(A_BOLD);
            attroff(COLOR_PAIR(5));
        }
    }
    freeifaddrs(ifaddr);
    refresh();
    return;
}
