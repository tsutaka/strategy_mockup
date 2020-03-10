
//マクロ定義
#define moji(abc) abc, (int)strlen(abc)
#define rad(abc)  revdig(abc) * 3.141592 / 180.000

//定数宣言
#define TIMER_ID1 1					//1/60秒タイマー
#define TIMER_ID2 2					//1秒タイマー

#define TIME1 1000/60				//描画速度s
#define TIME2 2000 					//命令実行速度s
#define TIME3 30					//クロックの倍速指定　0:一秒を一秒60:一秒を一分

#define FIELDWMAX 5000				//フィールド幅
#define FIELDHMAX 5000				//フィールド高
#define POSMAX 10					//マップ罫線最大
#define MSG_XPOS 250				//情報欄のclw-x座標
#define CMD_XPOS 0					//命令入力欄のx座標
#define CMD_YPOS 0					//命令入力欄のy座標
#define CHECK_XPOS 400				//チェックテキストのx座標
#define CHECK_YPOS 200				//チェックテキストのy座標
#define STR_HEIGHT 20				//文字列の高さ

#define SIZE0 160					//部隊（極大）のマップ上サイズ
#define SIZE1 100					//部隊（大）のマップ上サイズ
#define SIZE2 50					//部隊（中）のマップ上サイズ
#define SIZE3 20					//部隊（小）のマップ上サイズ
#define SIZE4 5						//部隊（極小）のマップ上サイズ

#define CMD_QUEUEMAX 10				//命令格納用スタックの大きさ
#define MSG_QUEUEMAX 10				//情報格納用スタックの大きさ
#define TEAMMAX 2					//最大チーム数
#define UNITMAX 20					//各チーム最大ユニット数
#define CHUMAX 10					//最大中隊数
#define SHOMAX 100					//最大小隊数
#define MARKPOINT 4					//ユニットの表示マークの座標数

#define INITCMD "1 1 1 A"			//初期設定用


//列挙体宣言
typedef enum {
	STAT_HCS,			//総司令、中隊司令、補給部隊
	STAT_HC,			//総司令、中隊司令
	STAT_CS,			//中隊司令、補給部隊
	STAT_H,				//総司令
	STAT_C,				//中隊司令
	STAT_S,				//補給部隊
	STAT_N,				//通常部隊
} unit_stat;
typedef enum {
	TYPE_F,				//歩兵
	TYPE_C,				//騎兵
	TYPE_LG,			//軽砲兵
	TYPE_HG,			//重砲兵
	TYPE_M,				//伝令
} unit_type;
typedef enum {          //*は接敵時の行動をかねる
	ACT_ATK,			//交戦*
	ACT_BUSY,			//処理
	ACT_ESCAPE,			//撤退*
	ACT_MOVE,			//移動
	ACT_STAY,			//停止
	ACT_SEARCH,			//索敵
	ACT_SLEEP,			//野営
	ACT_KEEP,			//維持*
} unit_action;
typedef enum {
	WLD_READY,			//準備
	WLD_MAINGAME,		//メインゲーム
	WLD_PAUSE,			//ポーズ中
} world_stat;
	

//変数宣言
char command[256] = INITCMD;		//命令入力用
char checktext[256] = "";			//文字列チェック用
int clw = 0, clh = 0;				//ウィンドウサイズ
int MYTEAM = 0, MYUNIT = 0;			//自分のチーム、自分のユニット


//構造体宣言

/*文字列ポインタの配列を避けるため以下のように構造体を使った*/
typedef struct {
	double x;						//x座標
	double y;						//y座標
} PNT;
typedef struct {
	char cmd[256];					//命令履歴用キュー
} CMD_QUEUE;
typedef struct {
	char msg[256];					//情報履歴用キュー
} MSG_QUEUE;
typedef struct {
	int flag;							//使用済みフラグ
	unit_action action;					//現在の行動
	unit_action reaction;				//接敵時の行動
	unit_stat stat;						//部隊ステータス
	unit_type type;						//兵種
	double dir;							//現在の向き
	double xpos;						//現在のx座標
	double ypos;						//現在のy座標
	double tardir;						//目標の向き
	double tarxpos;						//目標のx座標
	double tarypos;						//目標のy座標
	int wait;							//定員
	int hpmax;							//定員
	int hp;								//兵数
	int fusho;							//負傷兵数
	int horse;							//騎馬
	int lightgun;						//軽砲
	int heavygun;						//重砲
	int shiki;							//部隊士気
	int chutai;							//中隊番号
	int shotai;							//小隊番号
	int movpoint;						//移動力
	int atcpoint;						//攻撃力
	int itlpoint;						//知力
	CMD_QUEUE cmd_queue[CMD_QUEUEMAX];	//命令キュー
	MSG_QUEUE msg_queue[MSG_QUEUEMAX];	//情報キュー
}UNIT_DATA;
UNIT_DATA unit_[TEAMMAX][UNITMAX];

typedef struct {
	long time;					//現在時刻
	int unitnum[TEAMMAX];		//ユニット数
	int allhp[TEAMMAX];			//のこり兵力
	int shikiave[TEAMMAX];		//士気平均
	world_stat now_stat;		//現在の状況
} WORLDDATA;
WORLDDATA world_;