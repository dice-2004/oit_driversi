#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>

// モードの定義
#define RECEIVE 0
#define SEND 1

// グローバル変数としてファイルディスクリプタを定義
// このfdは、事前にsocket(), accept(), connect()などで設定されている想定
int fd;

/**
 * @brief モードに応じて座標データを送受信する
 * @param coordinate 送受信するデータ配列 (要素数3を想定: x, y, pass_flag)
 * @param mode SEND または RECEIVE
 * @return 処理後のcoordinate配列のポインタ
 */
int* run_SeRe_data(int coordinate[], int mode) {
    // coordinate配列のバイトサイズを計算 (int型が3つ分)
    const size_t data_size = sizeof(int) * 3;

    if (mode == SEND) {
        // --- 送信側の処理 ---
        printf("[Sender]   Sending data: x=%d, y=%d, flag=%d\n",
               coordinate[0], coordinate[1], coordinate[2]);

        // writeシステムコールでデータをfdに書き込む
        if (write(fd, coordinate, data_size) == -1) {
            perror("write() error");
            // エラー時は何らかの終了処理が必要
        }
    }
    else if (mode == RECEIVE) {
        // --- 受信側の処理 ---
        printf("[Receiver] Waiting for data...\n");

        // readシステムコールでfdからデータを読み込む
        ssize_t read_bytes = read(fd, coordinate, data_size);
        if (read_bytes == -1) {
            perror("read() error");
            // エラー処理
        } else if (read_bytes == 0) {
            // 相手が接続を切った場合
            printf("[Receiver] Connection closed by peer.\n");
        } else {
            printf("[Receiver] Received data: x=%d, y=%d, flag=%d\n",
                   coordinate[0], coordinate[1], coordinate[2]);
        }
    }

    return coordinate;
}

// 上記のrun_SeRe_data関数がこの下にある想定で進めます

int main() {
    int sp_fds[2]; // socketpair用のfd配列
    pid_t pid;

    // 擬似的な通信路を作成
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sp_fds) == -1) {
        perror("socketpair() error");
        return 1;
    }

    // プロセスを複製 (送信側と受信側を作るため)
    pid = fork();
    if (pid == -1) {
        perror("fork() error");
        return 1;
    }

    if (pid > 0) {
        // --- 親プロセス (送信側) ---
        fd = sp_fds[0]; // 通信には0番目のfdを使用
        close(sp_fds[1]); // 使わないfdは閉じる

        // 送信するデータを作成 (x=5, y=3, pass_flag=0)
        int my_coordinate[3] = {5, 3, 0};

        // SENDモードで関数を実行
        run_SeRe_data(my_coordinate, SEND);

        // 子プロセスの終了を待つ
        wait(NULL);
        printf("Parent process finished.\n");

    } else {
        // --- 子プロセス (受信側) ---
        fd = sp_fds[1]; // 通信には1番目のfdを使用
        close(sp_fds[0]); // 使わないfdは閉じる

        // 受信用の空のデータ配列
        int received_coordinate[3];

        // RECEIVEモードで関数を実行
        run_SeRe_data(received_coordinate, RECEIVE);

        printf("Child process finished.\n");
    }

    // 使用したfdを閉じる
    close(fd);

    return 0;
}
