
//�}�N����`
#define moji(abc) abc, (int)strlen(abc)
#define rad(abc)  revdig(abc) * 3.141592 / 180.000

//�萔�錾
#define TIMER_ID1 1					//1/60�b�^�C�}�[
#define TIMER_ID2 2					//1�b�^�C�}�[

#define TIME1 1000/60				//�`�摬�xs
#define TIME2 2000 					//���ߎ��s���xs
#define TIME3 30					//�N���b�N�̔{���w��@0:��b����b60:��b���ꕪ

#define FIELDWMAX 5000				//�t�B�[���h��
#define FIELDHMAX 5000				//�t�B�[���h��
#define POSMAX 10					//�}�b�v�r���ő�
#define MSG_XPOS 250				//��񗓂�clw-x���W
#define CMD_XPOS 0					//���ߓ��͗���x���W
#define CMD_YPOS 0					//���ߓ��͗���y���W
#define CHECK_XPOS 400				//�`�F�b�N�e�L�X�g��x���W
#define CHECK_YPOS 200				//�`�F�b�N�e�L�X�g��y���W
#define STR_HEIGHT 20				//������̍���

#define SIZE0 160					//�����i�ɑ�j�̃}�b�v��T�C�Y
#define SIZE1 100					//�����i��j�̃}�b�v��T�C�Y
#define SIZE2 50					//�����i���j�̃}�b�v��T�C�Y
#define SIZE3 20					//�����i���j�̃}�b�v��T�C�Y
#define SIZE4 5						//�����i�ɏ��j�̃}�b�v��T�C�Y

#define CMD_QUEUEMAX 10				//���ߊi�[�p�X�^�b�N�̑傫��
#define MSG_QUEUEMAX 10				//���i�[�p�X�^�b�N�̑傫��
#define TEAMMAX 2					//�ő�`�[����
#define UNITMAX 20					//�e�`�[���ő僆�j�b�g��
#define CHUMAX 10					//�ő咆����
#define SHOMAX 100					//�ő召����
#define MARKPOINT 4					//���j�b�g�̕\���}�[�N�̍��W��

#define INITCMD "1 1 1 A"			//�����ݒ�p


//�񋓑̐錾
typedef enum {
	STAT_HCS,			//���i�߁A�����i�߁A�⋋����
	STAT_HC,			//���i�߁A�����i��
	STAT_CS,			//�����i�߁A�⋋����
	STAT_H,				//���i��
	STAT_C,				//�����i��
	STAT_S,				//�⋋����
	STAT_N,				//�ʏ핔��
} unit_stat;
typedef enum {
	TYPE_F,				//����
	TYPE_C,				//�R��
	TYPE_LG,			//�y�C��
	TYPE_HG,			//�d�C��
	TYPE_M,				//�`��
} unit_type;
typedef enum {          //*�͐ړG���̍s�������˂�
	ACT_ATK,			//���*
	ACT_BUSY,			//����
	ACT_ESCAPE,			//�P��*
	ACT_MOVE,			//�ړ�
	ACT_STAY,			//��~
	ACT_SEARCH,			//���G
	ACT_SLEEP,			//��c
	ACT_KEEP,			//�ێ�*
} unit_action;
typedef enum {
	WLD_READY,			//����
	WLD_MAINGAME,		//���C���Q�[��
	WLD_PAUSE,			//�|�[�Y��
} world_stat;
	

//�ϐ��錾
char command[256] = INITCMD;		//���ߓ��͗p
char checktext[256] = "";			//������`�F�b�N�p
int clw = 0, clh = 0;				//�E�B���h�E�T�C�Y
int MYTEAM = 0, MYUNIT = 0;			//�����̃`�[���A�����̃��j�b�g


//�\���̐錾

/*������|�C���^�̔z�������邽�߈ȉ��̂悤�ɍ\���̂��g����*/
typedef struct {
	double x;						//x���W
	double y;						//y���W
} PNT;
typedef struct {
	char cmd[256];					//���ߗ���p�L���[
} CMD_QUEUE;
typedef struct {
	char msg[256];					//��񗚗�p�L���[
} MSG_QUEUE;
typedef struct {
	int flag;							//�g�p�ς݃t���O
	unit_action action;					//���݂̍s��
	unit_action reaction;				//�ړG���̍s��
	unit_stat stat;						//�����X�e�[�^�X
	unit_type type;						//����
	double dir;							//���݂̌���
	double xpos;						//���݂�x���W
	double ypos;						//���݂�y���W
	double tardir;						//�ڕW�̌���
	double tarxpos;						//�ڕW��x���W
	double tarypos;						//�ڕW��y���W
	int wait;							//���
	int hpmax;							//���
	int hp;								//����
	int fusho;							//��������
	int horse;							//�R�n
	int lightgun;						//�y�C
	int heavygun;						//�d�C
	int shiki;							//�����m�C
	int chutai;							//�����ԍ�
	int shotai;							//�����ԍ�
	int movpoint;						//�ړ���
	int atcpoint;						//�U����
	int itlpoint;						//�m��
	CMD_QUEUE cmd_queue[CMD_QUEUEMAX];	//���߃L���[
	MSG_QUEUE msg_queue[MSG_QUEUEMAX];	//���L���[
}UNIT_DATA;
UNIT_DATA unit_[TEAMMAX][UNITMAX];

typedef struct {
	long time;					//���ݎ���
	int unitnum[TEAMMAX];		//���j�b�g��
	int allhp[TEAMMAX];			//�̂��蕺��
	int shikiave[TEAMMAX];		//�m�C����
	world_stat now_stat;		//���݂̏�
} WORLDDATA;
WORLDDATA world_;