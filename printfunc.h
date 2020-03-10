void print_unit(HDC hdc){//部隊の表示
	HGDIOBJ hOb;
	POINT pt[MARKPOINT];
	for(int team = 0; team < TEAMMAX; team++){
	    for(int unit = 0; unit < UNITMAX; unit++){
			if(unit_[team][unit].flag){//表示条件　距離判定も後々追加＠
				if(team == 1)	hOb = CreatePen(PS_SOLID, 1, RGB(255,0,0));
				else			hOb = CreatePen(PS_SOLID, 1, RGB(0,0,255));
				SelectObject(hdc, hOb);
				init_mark(pt, team, unit);
				Polyline(hdc, pt, MARKPOINT);
				DeleteObject(hOb);
			}
		}
	}
	return;
}
void print_cmdbox(HDC hdc){//命令の表示
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255,100,0));
	TextOut(hdc, CMD_XPOS, CMD_YPOS, moji(command));
	for(int i = 0; i < CMD_QUEUEMAX; i++){
		TextOut(hdc, CMD_XPOS, CMD_YPOS + STR_HEIGHT * (i+1)
			, moji(unit_[MYTEAM][MYUNIT].cmd_queue[i].cmd));
	}
	return;
}
void print_msgbox(HDC hdc){//情報の表示
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(0,100,255));
	for(int i = 0; i < MSG_QUEUEMAX; i++){
    	SetTextColor(hdc, RGB(0,100-i*10,255-i*20));
		TextOut(hdc, clw - MSG_XPOS, clh - STR_HEIGHT * (i + 1)
			, moji(unit_[MYTEAM][MYUNIT].msg_queue[i].msg));
	}
	return;
}
void print_chktxt(HDC hdc){//チェックテキストの表示
	SetTextColor(hdc, RGB(255,255,255));
	TextOut(hdc, clw / 2 - strlen(checktext)*10 / 2, 0, moji(checktext));
	return;
}
void print_info(HDC hdc){//基本情報表示
	char str[256] = "", temp1[32] = "", temp2[32] = "";
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(50,255,50));
	
	timetostr(world_.time, temp1);
	sprintf(str, "%s", temp1);
	TextOut(hdc, clw - 200, STR_HEIGHT * 0, moji(str));
	
	if(MYTEAM == 1)	strcpy(temp1, "赤");
	else			strcpy(temp1, "青");
	sprintf(str, "%s軍 %02d中隊所属 %02d小隊", 
		temp1, unit_[MYTEAM][MYUNIT].chutai, unit_[MYTEAM][MYUNIT].shotai);
	TextOut(hdc, clw - 200, STR_HEIGHT * 1, moji(str));
	
	stattostr(unit_[MYTEAM][MYUNIT].stat, temp1);
	typetostr(unit_[MYTEAM][MYUNIT].type, temp2);
	sprintf(str, "%s:%s", temp2, temp1);
	TextOut(hdc, clw - 200, STR_HEIGHT * 2, moji(str));
	
	sprintf(str, "兵数 %d(%d)/%d", unit_[MYTEAM][MYUNIT].hp, 
		unit_[MYTEAM][MYUNIT].fusho, unit_[MYTEAM][MYUNIT].hpmax);
	TextOut(hdc, clw - 200, STR_HEIGHT * 3, moji(str));
	
	sprintf(str, "士気 %d%%", unit_[MYTEAM][MYUNIT].shiki);
	TextOut(hdc, clw - 200, STR_HEIGHT * 4, moji(str));
	
	digtostr(unit_[MYTEAM][MYUNIT].dir, temp1);
	sprintf(str, "(%s:%0.0f, %0.0f)", temp1, 
		unit_[MYTEAM][MYUNIT].xpos, unit_[MYTEAM][MYUNIT].ypos);
	TextOut(hdc, clw - 200, STR_HEIGHT * 5, moji(str));
	
	digtostr(unit_[MYTEAM][MYUNIT].tardir, temp1);
	acttostr(unit_[MYTEAM][MYUNIT].action, temp2);
	sprintf(str, "%s,(%s:%0.0f, %0.0f)", temp2, temp1, 
		unit_[MYTEAM][MYUNIT].tarxpos, unit_[MYTEAM][MYUNIT].tarypos);
	TextOut(hdc, clw - 200, STR_HEIGHT * 6, moji(str));
	
	acttostr(unit_[MYTEAM][MYUNIT].reaction, temp2);
	sprintf(str, "接敵時:%s,", temp2);
	TextOut(hdc, clw - 200, STR_HEIGHT * 7, moji(str));
	return;
}