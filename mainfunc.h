
void select(char str[]){
	int team, chu, sho, x, y;
	int space = 0;
	double dir = 0;
	char tmp[256] = "", time[256] = "";
	//���@�̏��
	if(str[0] == ' '){
		MessageBox(NULL, "�擪�ɋ󔒂�����܂�", "�m�F", MB_OK);
		return;
	}
	if(str[strlen(str)-1] == ' '){
		MessageBox(NULL, "�����ɋ󔒂�����܂�", "�m�F", MB_OK);
		return;
	}
	for(int i = 1;str[i] != '\0';i++){
		if(str[i] == ' ' && str[i-1] == ' '){
			MessageBox(NULL, "�󔒂��A�����Ă��܂�", "�m�F", MB_OK);
			return;
		}
	}
	for(int i = 0;str[i] != '\0';i++){
		if(str[i] == ' ') space++;
		if(!((str[i] >= 'A' && str[i] <= 'J') || 
			(str[i] >= '0' && str[i] <= '9') || str[i] == ' ')){
			MessageBox(NULL, "�s���ȕ������܂܂�Ă��܂�", "�m�F", MB_OK);
			return;
		}
	}
	if(space != 3){
		MessageBox(NULL, "�f�[�^����4�ł͂���܂���", "�m�F", MB_OK);
		return;
	}
	//sscanf(str, "%d%d%d%d", team, chu, sho, x);
	str_get(str, tmp);
	team = atoi(tmp);
	str_get(str, tmp);
	chu = atoi(tmp);
	str_get(str, tmp);
	sho = atoi(tmp);
	str_get(str, tmp);
	if(strlen(tmp) != 1){
		MessageBox(NULL, "var4�̓��͂��s���ł�", "�m�F", MB_OK);
		return;
	}
	x = tmp[0];
	//sprintf(checktext, "%d,%d,%d,%d\n", team, chu, sho, x);

	if(team < 0 || team >= TEAMMAX){
		MessageBox(NULL, "var1�̓��͒l���͈͂𒴂��Ă��܂�", "�m�F", MB_OK);
		return;
	}
	if(chu < 0 || chu >= CHUMAX){
		MessageBox(NULL, "var2�̓��͒l���͈͂𒴂��Ă��܂�", "�m�F", MB_OK);
		return;
	}
	if(sho < 0 || sho >= SHOMAX){
		MessageBox(NULL, "var3�̓��͒l���͈͂𒴂��Ă��܂�", "�m�F", MB_OK);
		return;
	}
	if(x < 'A' || x >= 'J'){
		MessageBox(NULL, "var4�̓��͒l���͈͂𒴂��Ă��܂�", "�m�F", MB_OK);
		return;
	}
	MYTEAM = team;
	if(MYTEAM == 0)	dir = 180;
	else			dir = 0;
	//�o�����W�̐ݒ聗
	//���@�̐ݒ�
	init_unit(MYTEAM, MYUNIT, STAT_HCS, TYPE_F, 
	dir, 100.000, 100.000, 500, chu, sho);
	
	//�G�@�̐ݒ�
	init_unit(next_team(MYTEAM), 0, STAT_HCS, TYPE_F, 
	dir - 180, 100.000, 200.000, 500, rand()%100, rand()%100);
	//sprintf(checktext, "%d,%d\n",next_unit(MYTEAM), 0);
	
	strcpy(str, "");
	world_.now_stat = WLD_MAINGAME;		//�Q�[�����[�h��i�s
	msg_clear(MYTEAM, MYUNIT);          //��񗓂̃N���A
	timetostr(world_.time, time);       //���ݎ����̕�����擾
	sprintf(tmp, "%s>�J��", time);      //�J�퍐�m
	msg_enqueue(tmp, MYTEAM, MYUNIT);
	return;
}
void cmdrecv(char command[]){
 char temp1[256] = "", temp2[256] = "", temp3[256] = "";
 char message1[256] = "";

	if(strcmp(command, "") == 0) return;			//���߂Ȃ�
	if(strcmp(command, "progress") == 0){//�O�i
		unit_[MYTEAM][MYUNIT].action = ACT_MOVE;
		sprintf(message1, "%02d����:", unit_[MYTEAM][MYUNIT].shotai);
		strcat(message1, "�O�i");
		msg_enqueue(message1, MYTEAM, MYUNIT);
	}
	else if(strncmp(command, "turnright", strlen("turnright")) == 0){   //�E�]�i	���ꕶ������n�܂閽�߂͒������̂��珑��
		str_get(command, temp2);
		unit_[MYTEAM][MYUNIT].tardir = unit_[MYTEAM][MYUNIT].dir + revdig(atoi(command));
		msg_enqueue("�E�]�i", MYTEAM, MYUNIT);
	}
	else if(strncmp(command, "turnleft", strlen("turnleft")) == 0){   //���]�i
		str_get(command, temp2);
		unit_[MYTEAM][MYUNIT].tardir = unit_[MYTEAM][MYUNIT].dir - revdig(atoi(command));
		msg_enqueue("���]�i", MYTEAM, MYUNIT);
	}
	else if(strncmp(command, "turn", strlen("turn")) == 0){   //�]�i
		str_get(command, temp2);
		if(isdir(command)) unit_[MYTEAM][MYUNIT].tardir = strtodig(command);
		else unit_[MYTEAM][MYUNIT].tardir = revdig(atoi(command));
		//sprintf(checktext, "%f\n", strtodig(command));
		msg_enqueue("�]�i", MYTEAM, MYUNIT);
	}
	else if(strcmp(command, "stop") == 0){//��~
		unit_[MYTEAM][MYUNIT].action = ACT_STAY;
		msg_enqueue("��~", MYTEAM, MYUNIT);
	}
	else if(strncmp(command, "cut", strlen("cut")) == 0){//����
		
		str_get(command, temp2);
		//��������؂�o��
		/*sprintf("%02d", temp2);
		init_unit(MYTEAM, MYUNIT, STAT_HCS, TYPE_F, 
			dir, 100.000, 100.000, 500, chu, sho);
		unit_[MYTEAM][MYUNIT].action = ACT_STAY;
		msg_enqueue("����", MYTEAM, MYUNIT);   */
	}
	else if(strncmp(command, "reaction", strlen("reaction")) == 0){//�ړG���̍s��
		str_get(command, temp2);
		if(strcmp(command, "attack") == 0) unit_[MYTEAM][MYUNIT].reaction = ACT_ATK;
		else if(strcmp(command, "escape") == 0) unit_[MYTEAM][MYUNIT].reaction = ACT_ESCAPE;
		else if(strcmp(command, "keep") == 0) unit_[MYTEAM][MYUNIT].reaction = ACT_KEEP;
		msg_enqueue("�ړG���ݒ�", MYTEAM, MYUNIT);
	}
	else if(strncmp(command, "wait", strlen("wait")) == 0){//�ҋ@
		str_get(command, temp2);
		unit_[MYTEAM][MYUNIT].wait = 60 * atoi(command);
		msg_enqueue("�ҋ@", MYTEAM, MYUNIT);
	}
	else {
		msg_enqueue("���ߕs��", MYTEAM, MYUNIT);
	}
 return;
}

void cmdproc(void){
 PNT pt;
 	if(unit_[MYTEAM][MYUNIT].wait != 0){//�E�F�C�g�^�C�}�̃J�E���g�_�E��
		unit_[MYTEAM][MYUNIT].wait--;
		if(unit_[MYTEAM][MYUNIT].wait < 0) unit_[MYTEAM][MYUNIT].wait = 0;
	}
	if(	((revdig(unit_[MYTEAM][MYUNIT].tardir) - revdig(unit_[MYTEAM][MYUNIT].dir) > 0) &&//��]����
		(revdig(unit_[MYTEAM][MYUNIT].tardir) - revdig(unit_[MYTEAM][MYUNIT].dir) < 180)) ||
		((revdig(unit_[MYTEAM][MYUNIT].tardir) - revdig(unit_[MYTEAM][MYUNIT].dir) > -360) &&
		(revdig(unit_[MYTEAM][MYUNIT].tardir) - revdig(unit_[MYTEAM][MYUNIT].dir) < -180)) ||
		((revdig(unit_[MYTEAM][MYUNIT].tardir) - revdig(unit_[MYTEAM][MYUNIT].dir) > 360) &&
		(revdig(unit_[MYTEAM][MYUNIT].tardir) - revdig(unit_[MYTEAM][MYUNIT].dir) < 540))	)
		unit_[MYTEAM][MYUNIT].dir++;
	else if(revdig(unit_[MYTEAM][MYUNIT].tardir) != revdig(unit_[MYTEAM][MYUNIT].dir)) unit_[MYTEAM][MYUNIT].dir--;
	switch(unit_[MYTEAM][MYUNIT].action){//���C���s������
	case ACT_MOVE:
		pt = movexy(unit_[MYTEAM][MYUNIT].dir, unit_[MYTEAM][MYUNIT].movpoint);
		unit_[MYTEAM][MYUNIT].xpos += pt.x;
		unit_[MYTEAM][MYUNIT].ypos += pt.y;
		break;
	}
	if(unit_[MYTEAM][MYUNIT].xpos < 0){//�ʒu���̕␳
		unit_[MYTEAM][MYUNIT].xpos = 0;
	}
	if(unit_[MYTEAM][MYUNIT].ypos < 0){
		unit_[MYTEAM][MYUNIT].ypos = 0;
	}
	if(unit_[MYTEAM][MYUNIT].xpos >= FIELDWMAX){
		unit_[MYTEAM][MYUNIT].xpos = FIELDWMAX-1;
	}
	if(unit_[MYTEAM][MYUNIT].ypos >= FIELDHMAX){
		unit_[MYTEAM][MYUNIT].ypos = FIELDHMAX-1;
	}
 return;
}