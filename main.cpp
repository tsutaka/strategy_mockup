#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "def.h"
#include "func.h"
#include "mainfunc.h"
#include "printfunc.h"

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

char szClassName[] = "main";	//�E�B���h�E�N���X


int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
				   LPSTR lpsCmdLine, int nCmdShow)
{
	MSG msg;
	BOOL bRet;
	
	if (!InitApp(hCurInst))
		return FALSE;
	if (!InitInstance(hCurInst, nCmdShow)) 
		return FALSE;
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1) {
			break;
		} else {
			TranslateMessage(&msg);//���b�Z�[�W��K�؂ɕϊ�
			DispatchMessage(&msg);//�E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗐M
		}
	}
	return (int)msg.wParam;//�v���O�������I��
}

//�E�B���h�E�E�N���X�̓o�^

ATOM InitApp(HINSTANCE hInst)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	//�v���V�[�W����
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;//�C���X�^���X
	wc.hIcon = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor = (HCURSOR)LoadImage(NULL,
		MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;	//���j���[��
	wc.lpszClassName = (LPCSTR)szClassName;
	wc.hIconSm = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	return (RegisterClassEx(&wc));
}

//�E�B���h�E�̐���

BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
	HWND hWnd;

	hWnd = CreateWindow(szClassName,
			"NWSSG", //�^�C�g���o�[�ɂ��̖��O���\������܂�
			WS_OVERLAPPEDWINDOW, //�E�B���h�E�̎��
			CW_USEDEFAULT,	//�w���W
			CW_USEDEFAULT,	//�x���W
			CW_USEDEFAULT,	//��
			CW_USEDEFAULT,	//����
			NULL, //�e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
			NULL, //���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
			hInst, //�C���X�^���X�n���h��
			NULL);
	if (!hWnd)
		return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

//�E�B���h�E�v���V�[�W��

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	PAINTSTRUCT ps;
	static RECT rc;
	HDC hdc;
	static char charc[256] = "";
	char temp[256];
	switch (msg) {//�����̋C�ɂȂ���̂ݎ󂯎��
		case WM_CREATE:
			#include "init.h"//������
			SetTimer(hWnd, TIMER_ID1, TIME1, NULL);//�^�C�}���Z�b�g
			SetTimer(hWnd, TIMER_ID2, TIME2, NULL);//�^�C�}���Z�b�g
			break;
		case WM_CHAR:
			if(wp == (WPARAM)VK_RETURN || wp == (WPARAM)VK_ESCAPE || 
			   wp == (WPARAM)VK_TAB || wp == (WPARAM)VK_BACK) break;
			wsprintf(charc, "%c", (char)wp);//�������͂̎󂯎��
			strcat(command, charc);//���ݕ�����̍X�V
			//MessageBox(hWnd, "���͂���", "�m�F", MB_OK);
			InvalidateRect(hWnd, NULL, TRUE);//�`�揈���Ăяo��
			break;
		case WM_KEYDOWN:
			switch(wp){
				case VK_BACK:
					str_bk(command);//���ݕ�����̖����폜
					break;
				case VK_RETURN://���񂽁[���͎�
					switch(world_.now_stat){
					case WLD_READY:
						select(command);
						break;
					case WLD_MAINGAME:
						cmd_enqueue(command, MYTEAM, MYUNIT);
						strcpy(command, "");
						break;
					case WLD_PAUSE:
						world_.now_stat = WLD_MAINGAME;
						strcpy(checktext, "");
						break;
					}
					strcpy(command, "");
					//MessageBox(hWnd, queue[0].cmd, "�֐��O", MB_OK);
					break;
				case VK_TAB:
					if(world_.now_stat == WLD_MAINGAME) world_.now_stat = WLD_PAUSE;
					else if(world_.now_stat == WLD_PAUSE) world_.now_stat = WLD_MAINGAME;
					strcpy(checktext, "");
					break;
				case VK_ESCAPE:
					PostQuitMessage(0);
					break;
				default:
					return DefWindowProc(hWnd, msg, wp, lp);
			}
			break;
		case WM_TIMER://�ʏ폈��
			if(wp == TIMER_ID1) {//1/60�b���ɕ`��
				//�m�C�̍X�V��
				GetClientRect(hWnd, &rc);
				clw = rc.right;//�E�B���h�E���̎擾
				clh = rc.bottom;//�E�B���h�E���̎擾
				InvalidateRect(hWnd, NULL, TRUE);//�`�揈���Ăяo��
				switch(world_.now_stat){
				case WLD_READY:
					break;
				case WLD_MAINGAME:
					//world�\���̂̍X�V�@���̑����ڂ̍X�V��
					world_.time++;
					//�����̈ړ������A�҂����Ԃ̌o�ߏ���
					cmdproc();
					break;
				case WLD_PAUSE:
					strcpy(checktext, "PAUSE");
					break;
				}
				break;
			}
			else if(wp == TIMER_ID2){//2�b���ɖ��߂̎��s
				switch(world_.now_stat){
				case WLD_READY:
					break;
				case WLD_MAINGAME:
					if(unit_[MYTEAM][MYUNIT].wait != 0) break;
				    strcpy(temp, cmd_dequeue(MYTEAM, MYUNIT));
					if(strcmp(temp, "") == 0) break;
					//MessageBox(hWnd, temp, "���ߎ�", MB_OK);
					cmdrecv(temp);
					break;
				case WLD_PAUSE:
					break;
				}
				InvalidateRect(hWnd, NULL, TRUE);//�`�揈���Ăяo��
			}
			return DefWindowProc(hWnd, msg, wp, lp);
		case WM_PAINT://�`�揈��
			hdc = BeginPaint(hWnd, &ps);//�f�o�C�X�R���e�L�X�g�̎擾
			
			//�����̕\��
			print_unit(hdc);
			//���߃{�b�N�X�̕`��
			print_cmdbox(hdc);
			//���{�b�N�X�̕`��
			print_msgbox(hdc);
			//�`�F�b�N�e�L�X�g�̕\��
			print_chktxt(hdc);
			//�C���t�H�̕\��
			print_info(hdc);
			
			EndPaint(hWnd, &ps);//�f�o�C�X�R���e�L�X�g�̊J��
			break;
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default://���̑��̏����̓f�t�H���g�ǂ���ɔC����
			return (DefWindowProc(hWnd, msg, wp, lp));
	}
	return 0;
}

