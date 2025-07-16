1(main)メインモジュール
```mermaid
graph TD
    main(開始) --> resize[[set_size<br>画面サイズ設定]];
    resize --> menue[[handle_menue<br>メニュー選択ハンドラ]];
    menue --> start[[start_game<br>オセロ開始]];
    start --> END(終了);

```

1.1(set_size)画面サイズ設定モジュール
```mermaid
graph TD
    resize(開始) -->  get --> kitei[/戻り値が正になるまで\];

    get[[getmaxyx<br>画面サイズ取得]];
    kitei --> resiz[[size_resize<br>ウィンドウサイズ変更]];
    resiz --> a[\戻り値が正になるまで/] --> END;
```

1.1.1(size_resize)画面サイズ強制変更関数
```mermaid
graph TD
    henkou(開始) --> g[画面に案内表示]
    --> henkou_s[画面サイズ変更];

    henkou_s --> a[画面に現在のサイズ表示] --> END(終了);
```

1.2(handle_menue)メニュー選択ハンドラモジュール
```mermaid
graph TD
    menue(開始) --> target[ハンドラ変数宣言<br>target = 1];


    target --> select[/遷移先<br>target == 0\];
    select -- 1 --> screen_top[screen_top<br>トップ画面] --> MU;
    select -- 2 --> screen_opponent[screen_opponent<br>対戦相手選択画面] --> MU;
    select -- 3 --> screen_help[screen_help<br>help画面] --> MU;
    select -- 4 --> screen_connect[screen_connect<br>接続方法選択画面] --> MU;
    select -- 5 --> screen_host[screen_host<br>「ホストになる」画面] --> MU;
    select -- 6 --> screen_connection[screen_guest<br>「接続する」画面] --> MU;

    MU[\遷移先/] -- 0 --> END(終了);
```

1.2.1(screen_top)トップ画面モジュール
```mermaid
graph TD
    screen_top(開始) --> dis[[display_top<br>トップ画面表示]];
    dis --> check[/キーバインド<br>bind → Space|Escape|Enter\];

    sa -- Enter | Space | Escape --> END(終了);
    check -- ↑ --> max{上に行けるか}
    max -- yes --> up[上に移動];
    max -- no --> display;

    check -- ↓ --> min{下に行けるか};
    min -- no --> display;
    min -- yes --> down[下に移動];



    up --> display[[display_top<br>トップ画面表示]] --> sa[\キーバインド/];
    down --> display;
```
1.2.1.1(display_top)トップ画面表示関数
```mermaid
graph TD
    top(開始) --> 画面初期化 --> in{引数};
    in -- 1 --> dis[画面表示];
    in -- 2 --> dis;
    in -- 3 --> dis;
    dis --> END(終了);
```

1.2.2(screen_opponent)対戦相手選択画面モジュール
```mermaid
graph TD
    screen_top(開始) --> dis[[display_opponent<br>対戦相手選択画面表示]];
    dis --> check[/キーバインド<br>bind → Escape | Enter\];

    check -- ↑ --> max{上に行けるか}
    max -- yes --> up[上に移動];
    max -- no --> display;
    check -- ↓ --> min{下に行けるか};
    min -- no --> display;
    min -- yes --> down[下に移動];



    up --> display[[display_opponent<br>対戦相手選択画面表示]] --> key[\キーバインド/];
    down --> display;
    key -- Escape | Enter --> END(終了);
```

1.2.2.1(display_opponent)対戦相手選択画面表示関数
```mermaid
graph TD
    top(開始) -->  画面初期化 --> in{引数};
    in -- 1 --> dis[画面表示];
    in -- 2 --> dis;
    dis --> END(終了);
```

1.2.3(screen_help)help画面モジュール
```mermaid
graph TD
    screen_help(開始) --> display[display_help<br>help画面表示];
    display --> E[/Enterバインド<br>bind → Enter\];
    a -- Enter --> END(終了);
    E -- other --> a[\Enterバインド/];
```
1.2.3.1(display_help)help画面表示関数
```mermaid
graph TD
    top(開始) --> o{ファイルがあるか};
    o -- yes --> dis[画面表示];
    o -- no --> END;
    dis --> END(終了);
```

1.2.4(screen_connect)接続方法選択画面モジュール
```mermaid
graph TD
    screen_top(開始) --> dis[[display_connect<br>接続方法選択画面表示]];
    dis --> check[/キーバインド<br>bind → Escape | Enter\];
    check -- ↑ --> max{上に行けるか}
    max -- yes --> up[上に移動];
    max -- no --> display;
    check -- ↓ --> min{下に行けるか};
    min -- no --> display;
    min -- yes --> down[下に移動];


    up --> display[[display_connect<br>接続方法選択画面表示]] --> f[\キーバインド/]-- Enter | Escape --> END(終了);
    down --> display;
```
1.2.4.1(display_connect)接続方法選択画面表示関数
```mermaid
graph TD
    top(開始) --> 画面初期化 --> in{引数};
    in -- 1 --> dis[画面表示];
    in -- 2 --> dis;
    dis --> END(終了);
```
1.2.5(screen_host)「ホストになる」画面モジュール
```mermaid
graph TD
    screen_host(開始) --> display[[display_host<br>「ホストになる」画面表示]];
    display --> select[[observ_connection<br>接続監視]];
    select --> END(終了);
```
1.2.5.1(display_host)「ホストになる」画面表示関数
```mermaid
graph TD
    top(開始) --> dis[画面表示];
    dis --> END(終了);
```
1.2.5.2(observ_connection)接続監視関数
```mermaid
graph TD
    obs(開始)  --> ob{モード識別子} -- 1 --> con[/接続されるまで\];
    ob -- 2 -->  ccd[/接続されるまで\];
    ccd --> dd{Escapeバインド};

    dd -- no --> x[/ホストIDの入力/]
    x --> q[相手に接続] --> f{相手が存在するか};
    f -- yes --> b;
    f -- no --> 接続エラーメッセージ --> b;
     b[\接続されるまで/];
    dd -- yes --> END;

    b --> END;

    con --> d{Escapeバインド};

    d -- yes --> END;
    d -- no --> a[\接続されるまで/] ;
    a--> END(終了);
```

1.2.6(screen_guest)「接続する」画面モジュール
```mermaid
graph TD
    screen_guest(開始) --> display[[display_guest<br>「接続する」画面表示]];
    display --> select[[observ_connection<br>接続監視]];
    select --> END(終了);
```
1.2.6.1(display_guest)「接続する」画面表示モジュール
```mermaid
graph TD
    top(開始) --> dis[画面表示];
    dis --> END(終了);
```

1.3(start_game)ゲーム開始モジュール
```mermaid
graph TD
    start(開始) --> Ini[[game_init_dis<br>画面初期化]];
    Ini --> bind[/キーバインド<br>bind → Escape\];

    Ebin -- Escape --> E[終了画面表示];
    E --> END;
    bind -- None --> judge_obs{両者バスしたか};
    judge_obs -- no --> run[[game_run<br>進行]];
    run --> Ebin;
    judge_obs -- yes --> judge[[game_judge<br>勝敗決定]];
    judge --> END(終了);
    Ebin[\キーバインド/];
```
1.3.1(game_init_sp)画面初期化
```mermaid
graph TD
    start(開始) -->  tips[画面を初期化];
    tips --> END(終了);
```


1.3.2(game_run)進行モジュール
```mermaid
graph TD
    run(開始) --> t{CUPまたはHOSTか}-- yes --> a{置ける場所があるか} -- yes --> select[[run_select_area<br>配置場所決定]];
    t -- no --> qw[[run_SeRe_data<br>データ送受信]] --> ads{相手がパスしたか} --  yes --> m;
    ads -- no --> sad[[run_update_area<br>配置更新]] --> bh[[run_update_display<br>画面更新]] --> m;
    select --> update[[run_update_area<br>配置更新]];
    update --> draw[[run_update_display<br>画面更新]] --> dadw{HOSTか}  -- yes　--> vgvf[[run_SeRe_data<br>データ送受信]] -->  m[メッセージ表示];
    a -- no --> dadw;
    dadw -- no --> m;
    CPU -- no -->send[[run_SeRe_data<br>データ送受信]];
    m --> gu{GUESTか} -- yes --> saf{おける場所があるか} -- no --> cacsa;
    saf -- yes -->  afas[[run_select_area<br>配置場所決定]] --> dau[[run_update_area<br>配置更新]] --> adad[[run_update_display<br>画面更新]] --> cacsa[[run_SeRe_data<br>データ送受信]] -->  me;
     gu -- no --> CPU{相手がCPUか};
    send --> b{相手がパスしたか};
    o -- yes --> se[配置場所を探す<br>アルゴリズム];
    se --> up[[run_update_area<br>配置更新]];
    up --> dr[[run_update_display<br>画面更新]];

    dr --> me[メッセージ表示];
    o -- no --> me;
    CPU -- yes --> o{置ける場所があるか};
    b -- yes --> me;
    b -- no --> update2[[run_update_area<br>配置更新]];
    update2 --> draw2[[run_update_display<br>画面更新]];
    draw2 --> me;
    me --> END(終了);
```

1.3.2.1(game_serch_placeable)配置可能場所探索関数
```mermaid
graph TD
    start(開始) --> all[/全マス探索するまで\];
    all --> allD[/全方向探索するまで\];
    allD --> ch{相手の色があるか};
    ch -- no --> ed[\全方向探索するまで/];
    ch -- yes --> side[/端に行くまで<br>自分の色が見つかるまで\];
    side --> one[１マス進める];
    one --> sidee[\端に行くまで<br>自分の色が見つかるまで/];
    sidee --> ed;
    ed --> alle[\全マス探索するまで/];
    alle --> E(終了);
```

1.3.2.2(run_select_area)配置場所決定関数
```mermaid
graph TD
    start(開始) --> key[/入力待ち<br>key → Enter\];
    key -- Space --> sp[[game_tips<br>ヒント表示]] --> Ekey;
    key -- ↑ --> max{上に行けるか};
    max -- yes --> up[上に移動];
    up --> Ekey;
    max -- no --> Ekey;
    key -- ↓ --> min{下に行けるか};
    min -- yes --> down[下に移動];
    down --> Ekey;
    min -- no --> Ekey;
    key -- → --> right{右に行けるか};
    right -- yes --> right2[右に移動];
    right2 --> Ekey;
    right -- no --> Ekey;
    key -- ← --> left{左に行けるか};
    left -- yes --> left2[左に移動];
    left2 --> Ekey;
    left -- no --> Ekey;
    Ekey -- Enter --> check{置ける場所か};
    check -- yes --> das[配列更新] --> mkda[メッセージを表示] --> END(終了);
    check -- no --> dis[メッセージを表示];
    dis --> key;
    Ekey[\入力待ち/];
```

1.3.2.2.1(game_tips)ヒント表示関数
```mermaid
graph TD
    start(開始) --> sda[ヒントを表示];
    sda　--> E(終了);
```

1.3.2.3(run_update_area)配置更新関数
```mermaid
graph TD
    start(開始) --> op[/全方向探索するまで\];
    op --> das{相手の色があるか};
    das -- yes --> sad[/端に行くまで<br>自分の色が見つかるまで\] --> co[1マス進める];
    co --> sade[\端に行くまで<br>自分の色が見つかるまで/];
    sade --> lll[\全方向探索するまで/];
    das -- no --> lll;
    lll --> END(終了);
```


1.3.2.4(run_update_display)画面更新関数
```mermaid
graph TD
    start(開始) --> o[オセロ表示画面の更新];
    o --> END(終了);
```

1.3.2.5(run_SeRe_data)データ送受信関数
```mermaid
graph TD
    start(開始) --> da[HOSTか] -- yes --> das[データをシリアライズ化] --> ddas[データを送信];
    da -- no --> dsada[データを受信] --> daeraf[データをデシリアライズ化];
    ddas --> END(終了);
    daeraf --> END;
```


1.3.3(game_judge)勝敗決定モジュール
```mermaid
graph TD
    start(開始) --> stone[[count_stone<br>石数検出]];
    stone --> dis[[display_result<br>勝敗画面表示]];
    dis --> END(終了);
```
1.3.3.1(count_stone)石数検出関数
```mermaid
graph TD
    start --> go[配列を探索];
    go --> l[/配列の最後まで\];
    l --> judge{取り出した要素};
    judge -- 1 --> white[白のカウント+1];
    judge -- -1 --> black[黒のカウント+1];
    judge -- 0 -->El;
    white -->El;
    black -->El;
    El[\配列の最後まで/] --> END(終了);
```
1.3.3.2(display_result)勝敗画面表示関数
```mermaid
graph TD
    start(開始) --> s{自分 ? 相手};
    s -- ＞ --> win[勝利画面を表示];
    s -- ＝ --> draw[引き分け画面を表示];
    s -- ＜ --> lose[敗北画面を表示];
    win --> END(終了);
    draw --> END;
    lose --> END;
```
