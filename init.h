
//乱数の初期化
srand(time(NULL));
//初期化
for(int cnt1 = 0; cnt1 < TEAMMAX; cnt1++){
    for(int cnt2 = 0; cnt2 < UNITMAX; cnt2++){
    	unit_[cnt1][cnt2].flag = 0;				//使用済みフラグ
    	unit_[cnt1][cnt2].action = ACT_STAY;	//現在の行動
    	unit_[cnt1][cnt2].reaction = ACT_ESCAPE;	//接敵時の行動
    	unit_[cnt1][cnt2].stat = STAT_N;    	//部隊ステータス
    	unit_[cnt1][cnt2].type = TYPE_F;		//兵種
    	unit_[cnt1][cnt2].dir = 0.0;			//現在の向き
    	unit_[cnt1][cnt2].xpos = 0.0;			//現在のx座標
    	unit_[cnt1][cnt2].ypos = 0.0;			//現在のy座標
    	unit_[cnt1][cnt2].tardir = 0.0;			//目標の向き
    	unit_[cnt1][cnt2].tarxpos = 0.0;		//目標のx座標
    	unit_[cnt1][cnt2].tarypos = 0.0;		//目標のy座標
    	unit_[cnt1][cnt2].wait = 0;				//残り待ち時間
    	unit_[cnt1][cnt2].hpmax = 0;			//定員
    	unit_[cnt1][cnt2].hp = 0;				//兵数
    	unit_[cnt1][cnt2].fusho = 0;			//負傷兵数
    	unit_[cnt1][cnt2].horse = 0;			//騎馬
    	unit_[cnt1][cnt2].lightgun = 0;			//軽砲
    	unit_[cnt1][cnt2].heavygun = 0;			//重砲
    	unit_[cnt1][cnt2].shiki = 0;			//部隊士気
    	unit_[cnt1][cnt2].chutai = 0;			//中隊番号
    	unit_[cnt1][cnt2].shotai = 0;			//小隊番号
    	unit_[cnt1][cnt2].movpoint = 0;			//移動力
    	unit_[cnt1][cnt2].atcpoint = 0;			//攻撃力
    	unit_[cnt1][cnt2].itlpoint = 0;			//知力
        for(int i = 0; i < CMD_QUEUEMAX; i++)
            strcpy(unit_[cnt1][cnt2].cmd_queue[i].cmd, "");
        for(int i = 0; i < MSG_QUEUEMAX; i++)
            strcpy(unit_[cnt1][cnt2].msg_queue[i].msg, "");
    }
}


msg_enqueue("初期設定を入力してください", MYTEAM, MYUNIT);
msg_enqueue("書式：var1 var2 var3 var4", MYTEAM, MYUNIT);
msg_enqueue("var1:チーム選択 [0:青, 1:赤]", MYTEAM, MYUNIT);
msg_enqueue("var2:中隊番号 [0-9]", MYTEAM, MYUNIT);
msg_enqueue("var3:小隊番号 [0-99]", MYTEAM, MYUNIT);
msg_enqueue("var4:初期位置 [A-J]", MYTEAM, MYUNIT);

world_.time = (rand()%(60*60*60*12))/TIME3;					//現在時刻
for(int i = 0; i < TEAMMAX; i++) world_.unitnum[i];			//ユニット数
for(int i = 0; i < TEAMMAX; i++) world_.allhp[i];			//残り兵力
for(int i = 0; i < TEAMMAX; i++) world_.shikiave[i];		//士気平均
world_.now_stat = WLD_READY;								//現在の状況