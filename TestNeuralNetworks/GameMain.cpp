#include "pch.h"
#include "GameMain.h"
#include "MyNeuralNetwork.h"

#define	MAX_DATA		3
#define MAX_PARAMS		SCREEN_WIDTH

void Game::Calculate()
{
	// ニューラルネットワークオブジェクトを生成する
	NeuralNetwork	neuralNetwork;

	// ニューラルネットワークを初期化する(入力層:1、隠れ層:20、出力層:1)
	neuralNetwork.Initialize(1, 40, 1);

	// 学習率を設定する
	// Setup learning rate
	neuralNetwork.SetLearningRate(0.2);

	// モメンタムを設定する
	// Setup momentum
	neuralNetwork.SetMomentum(true, 0.8);

	error = 1.0;
	int		count = 0;

	// 機械学習する
	while (error > 0.001 && count < 10000)
	{
		error = 0.0;
		count++;
		for (int i = 0; i < MAX_PARAMS; i++)
		{
			// 入力データをニューラルネットワークにセットする
			// 角度
			neuralNetwork.SetInput(0, double(i) / double(SCREEN_WIDTH));
			// sinデータ
			neuralNetwork.SetDesiredOutput(0, double(graph[i]) / double(SCREEN_HEIGHT));

			// 前方伝播する
			neuralNetwork.FeedForward();
			// 誤差を計算する
			error += neuralNetwork.CalculateError();
			// 誤差逆伝播する
			neuralNetwork.BackPropagate();
		}
		// 誤差を計算する
		error = error / MAX_PARAMS;
	}

	//neuralNetwork.DumpData("data.txt");

	// 学習後のニューラルネットワークの検証をおこなう
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		// ニューラルネットワークに角度を指定してsin関数の値を求める
		neuralNetwork.SetInput(0, i / double(SCREEN_WIDTH));
		neuralNetwork.FeedForward();
		aigraph[i] = float(neuralNetwork.GetOutput(0) * SCREEN_HEIGHT);
	}
}

void Game::Initialize()
{
	graph = std::vector<float>(SCREEN_WIDTH, SCREEN_HEIGHT - 10);
	aigraph = std::vector<float>(SCREEN_WIDTH, -1.f);
}

void Game::Update()
{
	if (!calculating)
	{
		int x, y;
		GetMousePoint(&x, &y);
		if (0 <= x && x < SCREEN_WIDTH)
		{
			if (GetMouseInput())
			{
				int srcX, srcY, dstX, dstY;
				if (x < lastX)
					srcX = x, dstX = lastX, srcY = y, dstY = lastY;
				else
					srcX = lastX, dstX = x, srcY = lastY, dstY = y;
				for (int ix = srcX; ix < dstX; ix++)
				{
					if (0 <= ix && ix < SCREEN_WIDTH)
					{
						float t = float(ix - srcX) / float(dstX - srcX);
						float iy = srcY + float(dstY - srcY) * t;
						graph[ix] = iy;
					}
				}
			}
			lastX = x;
			lastY = y;
		}

		bool key = GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1;
		static bool lastKey = key;
		if (!lastKey && key)
		{
			calculating = true;

			// 別スレッドで計算を行う
			std::thread([&] {
				Calculate();
				calculating = false;
				}).detach();
		}
		lastKey = key;
	}
}

void Game::Render()
{
	for (int i = 0; i < SCREEN_WIDTH - 1; i++)
	{
		DrawLineAA(float(i), graph[i], float(i) + 1.f, graph[i + 1], ColorCode::COLOR_WHITE);
		DrawLineAA(float(i), aigraph[i], float(i) + 1.f, aigraph[i + 1], ColorCode::COLOR_YELLOW);
		DrawFormatStringF(0.f, 30.f, ColorCode::COLOR_LIME, L"エラー: %.2f%%", float(error) * 100.f);
	}

	if (calculating)
	{
		static float t = 0;
		DrawStringF(0, 10 - abs(sin(t += .1f)) * 5, L"計算中", ColorCode::COLOR_LIME);
	}
}

void Game::Finalize()
{
}
