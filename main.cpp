#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "def.h"
#include "func.h"
#include "mainfunc.h"
#include "printfunc.h"

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

char szClassName[] = "main";	//ウィンドウクラス


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
			TranslateMessage(&msg);//メッセージを適切に変換
			DispatchMessage(&msg);//ウィンドウプロシージャにメッセージを送信
		}
	}
	return (int)msg.wParam;//プログラムを終了
}

//ウィンドウ・クラスの登録

ATOM InitApp(HINSTANCE hInst)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	//プロシージャ名
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;//インスタンス
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
	wc.lpszMenuName = NULL;	//メニュー名
	wc.lpszClassName = (LPCSTR)szClassName;
	wc.hIconSm = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	return (RegisterClassEx(&wc));
}

//ウィンドウの生成

BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
	HWND hWnd;

	hWnd = CreateWindow(szClassName,
			"NWSSG", //タイトルバーにこの名前が表示されます
			WS_OVERLAPPEDWINDOW, //ウィンドウの種類
			CW_USEDEFAULT,	//Ｘ座標
			CW_USEDEFAULT,	//Ｙ座標
			CW_USEDEFAULT,	//幅
			CW_USEDEFAULT,	//高さ
			NULL, //親ウィンドウのハンドル、親を作るときはNULL
			NULL, //メニューハンドル、クラスメニューを使うときはNULL
			hInst, //インスタンスハンドル
			NULL);
	if (!hWnd)
		return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

//ウィンドウプロシージャ

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	PAINTSTRUCT ps;
	static RECT rc;
	HDC hdc;
	static char charc[256] = "";
	char temp[256];
	switch (msg) {//自分の気になる情報のみ受け取る
		case WM_CREATE:
			#include "init.h"//初期化
			SetTimer(hWnd, TIMER_ID1, TIME1, NULL);//タイマをセット
			SetTimer(hWnd, TIMER_ID2, TIME2, NULL);//タイマをセット
			break;
		case WM_CHAR:
			if(wp == (WPARAM)VK_RETURN || wp == (WPARAM)VK_ESCAPE || 
			   wp == (WPARAM)VK_TAB || wp == (WPARAM)VK_BACK) break;
			wsprintf(charc, "%c", (char)wp);//文字入力の受け取り
			strcat(command, charc);//現在文字列の更新
			//MessageBox(hWnd, "入力あり", "確認", MB_OK);
			InvalidateRect(hWnd, NULL, TRUE);//描画処理呼び出し
			break;
		case WM_KEYDOWN:
			switch(wp){
				case VK_BACK:
					str_bk(command);//現在文字列の末尾削除
					break;
				case VK_RETURN://えんたー入力時
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
					//MessageBox(hWnd, queue[0].cmd, "関数外", MB_OK);
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
		case WM_TIMER://通常処理
			if(wp == TIMER_ID1) {//1/60秒毎に描画
				//士気の更新＠
				GetClientRect(hWnd, &rc);
				clw = rc.right;//ウィンドウ幅の取得
				clh = rc.bottom;//ウィンドウ高の取得
				InvalidateRect(hWnd, NULL, TRUE);//描画処理呼び出し
				switch(world_.now_stat){
				case WLD_READY:
					break;
				case WLD_MAINGAME:
					//world構造体の更新　その他項目の更新＠
					world_.time++;
					//部隊の移動処理、待ち時間の経過処理
					cmdproc();
					break;
				case WLD_PAUSE:
					strcpy(checktext, "PAUSE");
					break;
				}
				break;
			}
			else if(wp == TIMER_ID2){//2秒毎に命令の実行
				switch(world_.now_stat){
				case WLD_READY:
					break;
				case WLD_MAINGAME:
					if(unit_[MYTEAM][MYUNIT].wait != 0) break;
				    strcpy(temp, cmd_dequeue(MYTEAM, MYUNIT));
					if(strcmp(temp, "") == 0) break;
					//MessageBox(hWnd, temp, "命令受理", MB_OK);
					cmdrecv(temp);
					break;
				case WLD_PAUSE:
					break;
				}
				InvalidateRect(hWnd, NULL, TRUE);//描画処理呼び出し
			}
			return DefWindowProc(hWnd, msg, wp, lp);
		case WM_PAINT://描画処理
			hdc = BeginPaint(hWnd, &ps);//デバイスコンテキストの取得
			
			//部隊の表示
			print_unit(hdc);
			//命令ボックスの描画
			print_cmdbox(hdc);
			//情報ボックスの描画
			print_msgbox(hdc);
			//チェックテキストの表示
			print_chktxt(hdc);
			//インフォの表示
			print_info(hdc);
			
			EndPaint(hWnd, &ps);//デバイスコンテキストの開放
			break;
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default://その他の処理はデフォルトどおりに任せる
			return (DefWindowProc(hWnd, msg, wp, lp));
	}
	return 0;
}

