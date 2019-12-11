#include "pch.h"
#include "GameMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 未使用引数の警告対策
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);


	// デバッグ情報用ログファイルの出力の抑制
	SetOutApplicationLogValidFlag(FALSE);


	// 起動モードの設定
#if defined(_DEBUG)
	ChangeWindowMode(TRUE);	          // ウインドウモードで実行
	SetMainWindowText(GAME_TITLE);    // ウインドウタイトルの設定
	//SetWindowIconID(IDI_ICON1);       // ウインドウアイコンの設定
#else
	ChangeWindowMode(FALSE);	      // フルスクリーンで実行
#endif


	// 初期状態の画面モードの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);


	// DXライブラリの初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;    // エラーが起きたら直ちに終了
	}


	// 描画先を裏画面に設定
	SetDrawScreen(DX_SCREEN_BACK);

	Game game;

	// ゲームの処理
	game.Initialize();    // ゲームの初期化処理

	while (!ProcessMessage() && !CheckHitKey(EXIT_KEY))
	{
		game.Update();          // ゲームの更新処理
		game.Render();          // ゲームの描画処理

		ScreenFlip();          // 裏画面の内容を表画面に反映
		ClearDrawScreen();     // 裏画面の消去
	}

	game.Finalize();      // ゲームの終了処理


	// DXライブラリの終了処理
	DxLib_End();


	return 0;    // 正常終了
}
