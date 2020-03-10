//関数宣言
void str_bk(char *str){//文字列の末尾から一字削除
	int check=0;
	if(str[0] == '\0') return;
	for(int i = 0;str[i] != '\0';i++) check = i;
	str[check] = '\0';
	return;
}
void str_get(char str1[], char str2[]){//半角スペースでstr1を区切り,"str2 str1"に形成する
	char temp[256];
	int i;
	for(i = 0;str1[i] != '\0'; i++){
		if(str1[i] == ' '){
			str1[i] = '\0';
			i++;
			break;
		}
	}
	strcpy(temp, str1);
	strcpy(str1, &(str1[i]));
	strcpy(str2, temp);
	//MessageBox(NULL, str1, "確認", MB_OK);
	return;
}
int check_unit(int team){//指定チーム内の未使用ユニット番号を返す
    for(int unit = 0; unit < UNITMAX; unit++){
		if(unit_[team][unit].flag == 0) return unit;
	}
	return UNITMAX-1;//失敗時末尾のユニットを返す
}
int next_team(int team){//指定したチームじゃないチームを返す
	if(team == 0)return 1;
	if(team == 1)return 0;
}
double revdig(double dig){//ディグリーを0-359に変換
	while(!(dig < 360 && dig >= 0)){
		if(dig >= 360) dig -= 360;
		else if(dig < 0) dig += 360;
	}
	return dig;
}
int hptosize(int hp){//HPから大きさへ
	if(hp >= 1000) 	return SIZE0;
	if(hp >= 200) 	return SIZE1;
	if(hp >= 50) 	return SIZE2;
	if(hp >= 10) 	return SIZE3;
	return SIZE4;
}
void stattostr(unit_stat stat, char str[]){//ステータスを文字列に
	switch(stat){
	case STAT_HCS:	strcpy(str, "総司令部兼補給");		return;
	case STAT_HC:	strcpy(str, "総司令部");			return;
	case STAT_CS:	strcpy(str, "中隊司令兼補給");		return;
	case STAT_H:	strcpy(str, "総司令部");			return;
	case STAT_C:	strcpy(str, "中隊司令");			return;
	case STAT_S:	strcpy(str, "補給部隊");			return;
	case STAT_N:	strcpy(str, "通常部隊");			return;
	}
	strcpy(str, "不明");
	return;
}
void typetostr(unit_type type, char str[]){//兵種を文字列に
	switch(type){
	case TYPE_F:	strcpy(str, "歩兵");				return;
	case TYPE_C:	strcpy(str, "騎兵");				return;
	case TYPE_LG:	strcpy(str, "軽砲兵");				return;
	case TYPE_HG:	strcpy(str, "重砲兵");				return;
	case TYPE_M:	strcpy(str, "伝令");				return;
	}
	strcpy(str, "不明");
	return;
}
void acttostr(unit_type type, char str[]){//行動を文字列に
	switch(type){
	case ACT_ATK:		strcpy(str, "交戦中");			return;
	case ACT_BUSY:		strcpy(str, "処理中");			return;
	case ACT_ESCAPE:	strcpy(str, "撤退中");			return;
	case ACT_MOVE:		strcpy(str, "移動中");			return;
	case ACT_STAY:		strcpy(str, "停止中");			return;
	case ACT_SEARCH:	strcpy(str, "索敵中");			return;
	case ACT_SLEEP:		strcpy(str, "野営中");			return;
	case ACT_KEEP:		strcpy(str, "維持中");			return;
	}
	strcpy(str, "不明");
	return;
}
void digtostr(double dig, char str[]){//角度を文字列に
	dig = revdig(dig);
	if(22.5 > dig || 337.5 <= dig)			strcpy(str, "N");
	else if(22.5 <= dig && dig < 67.5)		strcpy(str, "NE");
	else if(67.5 <= dig && dig < 112.5)		strcpy(str, "E");
	else if(112.5 <= dig && dig < 157.5)	strcpy(str, "SE");
	else if(157.5 <= dig && dig < 202.5)	strcpy(str, "S");
	else if(202.5 <= dig && dig < 247.5)	strcpy(str, "SW");
	else if(247.5 <= dig && dig < 292.5)	strcpy(str, "W");
	else if(292.5 <= dig && dig < 337.5)	strcpy(str, "NW");
	else strcpy(str, "不明");
	return;
}
double strtodig(char str[]){//文字列を角度に
	if(		strcmp(str, "N")  == 0)		return 0;
	else if(strcmp(str, "NE") == 0)		return 45;
	else if(strcmp(str, "E")  == 0)		return 90;
	else if(strcmp(str, "SE") == 0)		return 135;
	else if(strcmp(str, "S")  == 0)		return 180;
	else if(strcmp(str, "SW") == 0)		return 225;
	else if(strcmp(str, "W")  == 0)		return 270;
	else if(strcmp(str, "NW") == 0)		return 315;
	return 0;
}
int isdir(char str[]){//文字列は角度か？
	if(		strcmp(str, "N")  == 0)		return 1;
	else if(strcmp(str, "NE") == 0)		return 1;
	else if(strcmp(str, "E")  == 0)		return 1;
	else if(strcmp(str, "SE") == 0)		return 1;
	else if(strcmp(str, "S")  == 0)		return 1;
	else if(strcmp(str, "SW") == 0)		return 1;
	else if(strcmp(str, "W")  == 0)		return 1;
	else if(strcmp(str, "NW") == 0)		return 1;
	return 0;
}
void timetostr(long time, char str[]){
	int dd, hh, mm, ss;
	ss = (time*TIME3/(60))%60;
	mm = (time*TIME3/(60))%60;		//経過分数%一時間の分
	hh = (time*TIME3/(60*60))%24;	//経過時間数%一日の時間
	dd = (time*TIME3/(60*60*24));	//経過日数
	sprintf(str, "%d日%02d:%02d", dd, hh, mm);
	return;
}
double kyori(double x, double y, double cx, double cy){
	   return pow(pow(x - cx, 2) + pow(y - cy, 2), (double)0.5);
}
PNT movexy(double dir, int length){//dir方向にlength動いた座標
	PNT pt;
	pt.x = (double)length * sin(rad(dir));
	pt.y = -1 * (double)length * cos(rad(dir));
	return pt;
}
PNT postoxy(char pos[]){
	PNT pt;
	pt.x = 0;
	pt.y = 0;
	if(strlen(pos) != 2) return pt;
	if(!((pos[0] >= 'A' && pos[0] <= 'J') || (pos[0] >= '0' && pos[0] <= '9'))) return pt;
	
	pt.x = FIELDWMAX * (pos[0] - 'A') / POSMAX + rand() % (FIELDWMAX / POSMAX);
	pt.y = FIELDHMAX * pos[1] / POSMAX + rand() % (FIELDHMAX / POSMAX);
	return pt;
}
void cmd_enqueue(char str[], int team, int unit){//命令をキューに入れる
	if(strcmp(str, "") == 0) return;
	for(int i = CMD_QUEUEMAX-1;i > 0;i--)
		strcpy(unit_[team][unit].cmd_queue[i].cmd, unit_[team][unit].cmd_queue[i - 1].cmd);
	strcpy(unit_[team][unit].cmd_queue[0].cmd, str);
	return;
}
char *cmd_dequeue(int team, int unit){//命令をキューから出す
	char dequeuout[256] = "";
	for(int i = CMD_QUEUEMAX-1;i >= 0;i--){
		if(strcmp(unit_[team][unit].cmd_queue[i].cmd, "") != 0){
			strcpy(dequeuout, unit_[team][unit].cmd_queue[i].cmd);
			strcpy(unit_[team][unit].cmd_queue[i].cmd, "");
			break;
		}
	}
	return dequeuout;
}
void cmd_clear(int team, int unit){//命令キューをクリア
	for(int i = 0; i < CMD_QUEUEMAX;i++){
		cmd_dequeue(team, unit);
	}
	return;
}
void msg_enqueue(char str[], int team, int unit){//情報をキューに入れる
	if(strcmp(str, "") == 0) return;
	for(int i = MSG_QUEUEMAX-1;i > 0;i--)
		strcpy(unit_[team][unit].msg_queue[i].msg, unit_[team][unit].msg_queue[i - 1].msg);
	strcpy(unit_[team][unit].msg_queue[0].msg, str);
	return;
}
char *msg_dequeue(int team, int unit){//情報をキューから出す
	static char dequeuout[256] = "";
	for(int i = MSG_QUEUEMAX-1;i >= 0;i--){
		if(strcmp(unit_[team][unit].msg_queue[i].msg, "") != 0){
			strcpy(dequeuout, unit_[team][unit].msg_queue[i].msg);
			strcpy(unit_[team][unit].msg_queue[i].msg, "");
			break;
		}
	}
	return dequeuout;
}
void msg_clear(int team, int unit){//情報キューをクリア
	for(int i = 0; i < MSG_QUEUEMAX;i++){
		msg_dequeue(team, unit);
	}
	return;
}
void turn_mark(POINT *mark, double dir, double cx, double cy){//与えられたpointをcx,cyを中心に回転
	double x[MARKPOINT], y[MARKPOINT];
	dir = revdig(dir);
	for(int i = 0;i < MARKPOINT;i++){
		x[i] = (double)mark[i].x - cx;
		y[i] = (double)mark[i].y - cy;
		mark[i].x = x[i] * cos(rad(dir)) - y[i] * sin(rad(dir)) + cx;
		mark[i].y = x[i] * sin(rad(dir)) + y[i] * cos(rad(dir)) + cy;
	}
	//sprintf(checktext, "%f,%f,%f(%d, %d)(%d,%d)(%d,%d)\n",dir,x,y, mark[0].x, mark[0].y, mark[1].x, mark[1].y, mark[2].x, mark[2].y);
	return;
}
int setteki(int teamnum, int unitnum){
	for(int unit = 0;unit < UNITMAX;unit++){
		if(kyori(unit_[teamnum][unitnum].xpos, unit_[teamnum][unitnum].ypos, 
		 		unit_[next_team(teamnum)][unit].xpos, unit_[next_team(teamnum)][unit].ypos) < 50){
		}
	}
	return 0;
}
void init_mark(POINT *mark, int teamnum, int unitnum){//部隊表示用の構造体を初期化
	int size;
	int x,y;
	size = hptosize(unit_[teamnum][unitnum].hp);
	//sprintf(checktext, "%d", size);
	x = unit_[teamnum][unitnum].xpos;
	y = unit_[teamnum][unitnum].ypos;
	mark[0].x = 0 + x;
	mark[0].y = y + (-1) * size /5;
	mark[1].x = x + (-1) * size /6;
	mark[1].y = y + size /5;
	mark[2].x = x + size /6;
	mark[2].y = y + size /5;
	mark[3].x = mark[0].x;
	mark[3].y = mark[0].y;
	//sprintf(checktext, "(%d, %d)(%d,%d)(%d,%d)\n",mark[0].x, mark[0].y, mark[1].x, mark[1].y, mark[2].x, mark[2].y);
	turn_mark(mark, unit_[teamnum][unitnum].dir, unit_[teamnum][unitnum].xpos, unit_[teamnum][unitnum].ypos);
	return;
}
void init_unit(int teamnum, int unitnum, unit_stat stat, unit_type type, 
	double dir, double x, double y, int hp, int chutai, int shotai)//部隊の初期化
{
	unit_[teamnum][unitnum].flag = TRUE;		//使用済みフラグ
	unit_[teamnum][unitnum].stat = stat;    	//部隊ステータス
	unit_[teamnum][unitnum].type = type;		//兵種
	unit_[teamnum][unitnum].dir = dir;			//現在の方向
	unit_[teamnum][unitnum].xpos = x;			//現在のx座標
	unit_[teamnum][unitnum].ypos = y;			//現在のy座標
	unit_[teamnum][unitnum].tardir = dir;		//目標の方向
	unit_[teamnum][unitnum].tarxpos = x;		//目標のx座標
	unit_[teamnum][unitnum].tarypos = y;		//目標のy座標
	unit_[teamnum][unitnum].hpmax = hp;			//定員
	unit_[teamnum][unitnum].hp = hp;			//兵数
	switch(type){
	case TYPE_C:
		unit_[teamnum][unitnum].horse = hp;		//騎馬
		break;
	case TYPE_LG:
		unit_[teamnum][unitnum].lightgun = hp;	//軽砲
		break;
	case TYPE_HG:
		unit_[teamnum][unitnum].heavygun = hp;	//重砲
		break;
	}
	unit_[teamnum][unitnum].chutai = chutai;			//中隊番号
	unit_[teamnum][unitnum].shotai = shotai;			//小隊番号
	unit_[teamnum][unitnum].movpoint = rand() % 3 + 1;	//移動力
	unit_[teamnum][unitnum].atcpoint = rand() % 3 + 1;	//攻撃力
	unit_[teamnum][unitnum].itlpoint = rand() % 3 + 1;	//知力
	return;
}