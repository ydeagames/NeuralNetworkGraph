#pragma once

constexpr const wchar_t* GAME_TITLE = L"ニューラルネットワーク";        // ゲームタイトル

// <画面>
constexpr const int SCREEN_WIDTH = 640;                  // 画面の幅[pixel]
constexpr const int SCREEN_HEIGHT = 480;                  // 画面の高さ[pixel]

class Game
{
private:
	int lastX, lastY;
	std::vector<float> graph;
	std::vector<float> aigraph;

public:
	void Calculate();

	// ゲームの初期化処理
	void Initialize();

	// ゲームの更新処理
	void Update();

	// ゲームの描画処理
	void Render();

	// ゲームの終了処理
	void Finalize();
};
