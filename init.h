
//�����̏�����
srand(time(NULL));
//������
for(int cnt1 = 0; cnt1 < TEAMMAX; cnt1++){
    for(int cnt2 = 0; cnt2 < UNITMAX; cnt2++){
    	unit_[cnt1][cnt2].flag = 0;				//�g�p�ς݃t���O
    	unit_[cnt1][cnt2].action = ACT_STAY;	//���݂̍s��
    	unit_[cnt1][cnt2].reaction = ACT_ESCAPE;	//�ړG���̍s��
    	unit_[cnt1][cnt2].stat = STAT_N;    	//�����X�e�[�^�X
    	unit_[cnt1][cnt2].type = TYPE_F;		//����
    	unit_[cnt1][cnt2].dir = 0.0;			//���݂̌���
    	unit_[cnt1][cnt2].xpos = 0.0;			//���݂�x���W
    	unit_[cnt1][cnt2].ypos = 0.0;			//���݂�y���W
    	unit_[cnt1][cnt2].tardir = 0.0;			//�ڕW�̌���
    	unit_[cnt1][cnt2].tarxpos = 0.0;		//�ڕW��x���W
    	unit_[cnt1][cnt2].tarypos = 0.0;		//�ڕW��y���W
    	unit_[cnt1][cnt2].wait = 0;				//�c��҂�����
    	unit_[cnt1][cnt2].hpmax = 0;			//���
    	unit_[cnt1][cnt2].hp = 0;				//����
    	unit_[cnt1][cnt2].fusho = 0;			//��������
    	unit_[cnt1][cnt2].horse = 0;			//�R�n
    	unit_[cnt1][cnt2].lightgun = 0;			//�y�C
    	unit_[cnt1][cnt2].heavygun = 0;			//�d�C
    	unit_[cnt1][cnt2].shiki = 0;			//�����m�C
    	unit_[cnt1][cnt2].chutai = 0;			//�����ԍ�
    	unit_[cnt1][cnt2].shotai = 0;			//�����ԍ�
    	unit_[cnt1][cnt2].movpoint = 0;			//�ړ���
    	unit_[cnt1][cnt2].atcpoint = 0;			//�U����
    	unit_[cnt1][cnt2].itlpoint = 0;			//�m��
        for(int i = 0; i < CMD_QUEUEMAX; i++)
            strcpy(unit_[cnt1][cnt2].cmd_queue[i].cmd, "");
        for(int i = 0; i < MSG_QUEUEMAX; i++)
            strcpy(unit_[cnt1][cnt2].msg_queue[i].msg, "");
    }
}


msg_enqueue("�����ݒ����͂��Ă�������", MYTEAM, MYUNIT);
msg_enqueue("�����Fvar1 var2 var3 var4", MYTEAM, MYUNIT);
msg_enqueue("var1:�`�[���I�� [0:��, 1:��]", MYTEAM, MYUNIT);
msg_enqueue("var2:�����ԍ� [0-9]", MYTEAM, MYUNIT);
msg_enqueue("var3:�����ԍ� [0-99]", MYTEAM, MYUNIT);
msg_enqueue("var4:�����ʒu [A-J]", MYTEAM, MYUNIT);

world_.time = (rand()%(60*60*60*12))/TIME3;					//���ݎ���
for(int i = 0; i < TEAMMAX; i++) world_.unitnum[i];			//���j�b�g��
for(int i = 0; i < TEAMMAX; i++) world_.allhp[i];			//�c�蕺��
for(int i = 0; i < TEAMMAX; i++) world_.shikiave[i];		//�m�C����
world_.now_stat = WLD_READY;								//���݂̏�