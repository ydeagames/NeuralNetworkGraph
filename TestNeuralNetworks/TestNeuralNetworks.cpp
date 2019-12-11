// TestNeuralNetworks.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//
#include "pch.h"

#include "MyNeuralNetwork.h"

// ニューラルネットワークは下記のライブラリを使用
// Book: AI for Game Developers, O'Reilly Media, Inc.
// Authors: David M. Bourg & Glenn Seemann
// Example: Neural Networks, Chapter 14

#define	MAX_DATA		3
#define MAX_PARAMS		73

// Sin関数データセット
float TrainingSet [MAX_PARAMS][MAX_DATA] =
{
	//  degree   radian   sin
	   { 0.0f,   0.000f,  0.000f},		// 0 degree 0
	   { 5.0f,   0.087f,  0.087f},
	   {10.0f,   0.175f,  0.174f},
	   {15.0f,   0.262f,  0.259f},
	   {20.0f,   0.349f,  0.342f},
	   {25.0f,   0.436f,  0.432f},
	   {30.0f,   0.524f,  0.500f},		// 30 degree 6
	   {35.0f,   0.611f,  0.574f},
	   {40.0f,   0.698f,  0.643f},
	   {45.0f,   0.785f,  0.707f},
	   {50.0f,   0.873f,  0.766f},
	   {55.0f,   0.960f,  0.819f},
	   {60.0f,   1.047f,  0.866f},		// 60 degree 12
	   {65.0f,   1.134f,  0.906f},
	   {70.0f,   1.222f,  0.940f},
	   {75.0f,   1.309f,  0.966f},
	   {80.0f,   1.399f,  0.985f},
	   {85.0f,   1.484f,  0.996f},
	   {90.0f,   1.571f,  1.000f},		// 90 degree 18
	   {95.0f,   1.658f,  0.996f},
	   {100.0f,  1.745f,  0.985f},
	   {105.0f,  1.833f,  0.966f},
	   {110.0f,  1.920f,  0.940f},
	   {115.0f,  2.007f,  0.906f},
	   {120.0f,  2.094f,  0.866f},		// 120 dgree 24
	   {125.0f,  2.182f,  0.819f},
	   {130.0f,  2.269f,  0.766f},
	   {135.0f,  2.356f,  0.707f},
	   {140.0f,  2.443f,  0.643f},
	   {145.0f,  2.531f,  0.574f},
	   {150.0f,  2.618f,  0.500f},		// 150 dgree 30
	   {155.0f,  2.705f,  0.423f},
	   {160.0f,  2.793f,  0.342f},
	   {165.0f,  2.880f,  0.259f},
	   {170.0f,  2.967f,  0.174f},
	   {175.0f,  3.054f,  0.087f},
	   {180.0f,  3.142f,  0.000f},		// 180 degree 36
	   {185.0f,  3.246f, -0.087f},
	   {190.0f,  3.316f, -0.174f},
	   {195.0f,  3.403f, -0.259f},
	   {200.0f,  3.491f, -0.342f},
	   {205.0f,  3.578f, -0.423f},
	   {210.0f,  3.665f, -0.500f},		// 210 degree 42
	   {215.0f,  3.752f, -0.574f},
	   {220.0f,  3.840f, -0.643f},
	   {225.0f,  3.927f, -0.707f},
	   {230.0f,  4.014f, -0.766f},
	   {235.0f,  4.102f, -0.819f},
	   {240.0f,  4.189f, -0.866f},		// 240 degree 48
	   {245.0f,  4.276f, -0.906f},
	   {250.0f,  4.363f, -0.940f},
	   {255.0f,  4.451f, -0.966f},
	   {260.0f,  4.538f, -0.985f},
	   {265.0f,  4.625f, -0.996f},
	   {270.0f,  4.712f, -1.000f},		// 270 degree 54
	   {275.0f,  4.800f, -0.996f},
	   {280.0f,  4.887f, -0.985f},
	   {285.0f,  4.974f, -0.966f},
	   {290.0f,  5.061f, -0.940f},
	   {295.0f,  5.149f, -0.906f},
	   {300.0f,  5.236f, -0.866f},		// 300 degree 60
	   {305.0f,  5.323f, -0.819f},
	   {310.0f,  5.411f, -0.766f},
	   {315.0f,  5.498f, -0.707f},
	   {320.0f,  5.585f, -0.643f},
	   {325.0f,  5.672f, -0.574f},
	   {330.0f,  5.760f, -0.500f},		// 330 degree 66
	   {335.0f,  5.847f, -0.423f},
	   {340.0f,  5.934f, -0.342f},
	   {345.0f,  6.021f, -0.259f},
	   {350.0f,  6.109f, -0.174f},
	   {355.0f,  6.196f, -0.087f},
	   {360.0f,  6.283f,  0.000f}		// 360 degree 72
};

int main() 
{
	// ニューラルネットワークオブジェクトを生成する
	NeuralNetwork	neuralNetwork;

	// ニューラルネットワークを初期化する(入力層:1、隠れ層:20、出力層:1)
	neuralNetwork.Initialize(1, 20, 1);

	// 学習率を設定する
	// Setup learning rate
	neuralNetwork.SetLearningRate(0.2);

	// モメンタムを設定する
	// Setup momentum
	neuralNetwork.SetMomentum(true, 0.8);

	double	error = 1.0;
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
			neuralNetwork.SetInput(0, TrainingSet[i][0] / 360.0f);
			// sinデータ
			neuralNetwork.SetDesiredOutput(0, ((TrainingSet[i][2] + 1.0f) * 0.5f));

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
	for (int degree = 0; degree <= 360 * 4; degree += 30)
	{
		// ニューラルネットワークに角度を指定してsin関数の値を求める
		neuralNetwork.SetInput(0, degree / 360.0f);
		neuralNetwork.FeedForward();
		std::cout.setf(std::ios::fixed);
		std::cout << std::setw(3) << degree << "°";
		std::cout << "sin(" << std::setw(5) << std::setprecision(2) << (neuralNetwork.GetOutput(0) * 2.0f) - 1.0f << ")";
		std::cout << "sin(" << std::setw(5) << std::setprecision(2) << sin(degree * 3.1415f / 180.f) << ")";
		std::cout << std::endl;
	}
	std::cout << "error = " << error * 100 << "%" << std::endl;
	
    return 0;
}

