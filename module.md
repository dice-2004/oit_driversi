gcc -o main.exe main.c 1_size/set_size.c 2_menue/handle_menue.c 2_menue/screen_connect.c 2_menue/screen_host.c 2_menue/screen_opponent.c 2_menue/screen_top.c 2_menue/screen_help.c -lncurses


1 メインモジュール
```mermaid
graph TD
	main[main<br>メインモジュール] --- resize[set_size<br>画面サイズ設定];
	main --- menue[handle_menue<br>メニュー選択ハンドラ];
	main --- game[start_game<br>オセロ開始];
```
1.1画面サイズ設定モジュール
```mermaid
graph TD
	resize[set_size<br>画面サイズ設定] --- i[getmaxyx<br>画面サイズ取得];;
	resize --- c[size_resize<br>画面サイズ強制変更];
```
1.2メニュー選択ハンドラモジュール
```mermaid
graph TD
    Menu[menue_select<br>メニュー選択ハンドラ] --- a{前に実行したものにより決定};
    a --- s[screen_top<br>トップ画面];
    a --- start[screen_opponent<br>対戦相手選択画面];
    a --- help[screen_help<br>help画面];
    a --- anyone[screen_connect<br>接続方法選択画面];
    a --- host[screen_host<br>「ホストになる」画面];
    a --- connect[screen_guest<br>「接続する」画面];
```
1.2.1トップ画面選択モジュール
```mermaid
graph TD
    s[screen_top<br>トップ画面] --- display[display_top<br>トップ画面表示];
```
1.2.2対戦相手選択画面モジュール
```mermaid
graph TD
    s[screen_opponent<br>対戦相手選択画面] --- display[display_opponent<br>対戦相手選択画面表示];
```
1.2.3help画面モジュール
```mermaid
graph TD
    He[screen_help<br>help画面] --- display[display_help<br>ヘルプ画面表示];
```
1.2.4接続方法選択モジュール
```mermaid
graph TD
    s[screen_connect<br>接続方法選択画面] --- display[display_connect<br>接続方法選択画面表示];
```
1.2.5「ホストになる」画面モジュール
```mermaid
graph TD
    s[screen_host<br>「ホストになる」画面] --- display[display_host<br>「ホストになる」画面表示];
    s --- con[observ_connection<br>接続監視];
```
1.2.6「接続する」画面モジュール
```mermaid
graph TD
    s[screen_guest<br>「接続する」画面] --- display[display_guest<br>「接続する」画面表示];
    s --- se[observ_connection<br>接続監視];
```

1.3ゲーム開始モジュール
```mermaid
graph TD
    Game[start_game<br>ゲーム開始] --- Ini[game_init_dis<br>画面初期化];
    Game --- run[game_run<br>進行];
    Game --- judge[game_judge<br>勝敗決定];
```

1.3.2進行モジュール
```mermaid
graph TD
    run[game_run<br>進行] --- dasdsa[game_serch_placeable<br>配置可能探索];
    run --- select[run_select_area<br>配置場所決定] --- dsa[game_tips<br>ヒント表示];
    run --- update[run_update_area<br>配置更新];
    run --- draw[run_update_display<br>画面更新];
    run --- send[run_SeRe_data<br>データ送受信];
    run --- info[run_display_message<br>メッセージ表示等];
```
1.3.3勝敗決定モジュール
```mermaid
graph TD
    judge[game_judge<br>勝敗決定] --- stone[count_stone<br>石数検出];
    judge --- display[display_result<br>勝敗画面表示];
```
