#include "pch.h"
#include "GameMain.h"
#include "MyNeuralNetwork.h"

#define	MAX_DATA		3
#define MAX_PARAMS		SCREEN_WIDTH

void Game::Calculate()
{
	// �j���[�����l�b�g���[�N�I�u�W�F�N�g�𐶐�����
	NeuralNetwork	neuralNetwork;

	// �j���[�����l�b�g���[�N������������(���͑w:1�A�B��w:20�A�o�͑w:1)
	neuralNetwork.Initialize(1, 40, 1);

	// �w�K����ݒ肷��
	// Setup learning rate
	neuralNetwork.SetLearningRate(0.2);

	// �������^����ݒ肷��
	// Setup momentum
	neuralNetwork.SetMomentum(true, 0.8);

	double	error = 1.0;
	int		count = 0;

	// �@�B�w�K����
	while (error > 0.001 && count < 10000)
	{
		error = 0.0;
		count++;
		for (int i = 0; i < MAX_PARAMS; i++)
		{
			// ���̓f�[�^���j���[�����l�b�g���[�N�ɃZ�b�g����
			// �p�x
			neuralNetwork.SetInput(0, double(i) / double(SCREEN_WIDTH));
			// sin�f�[�^
			neuralNetwork.SetDesiredOutput(0, double(graph[i]) / double(SCREEN_HEIGHT));

			// �O���`�d����
			neuralNetwork.FeedForward();
			// �덷���v�Z����
			error += neuralNetwork.CalculateError();
			// �덷�t�`�d����
			neuralNetwork.BackPropagate();
		}
		// �덷���v�Z����
		error = error / MAX_PARAMS;
	}

	//neuralNetwork.DumpData("data.txt");

	// �w�K��̃j���[�����l�b�g���[�N�̌��؂������Ȃ�
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		// �j���[�����l�b�g���[�N�Ɋp�x���w�肵��sin�֐��̒l�����߂�
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
		Calculate();
	}
	lastKey = key;
}

void Game::Render()
{
	for (int i = 0; i < SCREEN_WIDTH - 1; i++)
	{
		DrawLineAA(i, graph[i], i + 1, graph[i + 1], ColorCode::COLOR_WHITE);
		DrawLineAA(i, aigraph[i], i + 1, aigraph[i + 1], ColorCode::COLOR_YELLOW);
	}
}

void Game::Finalize()
{
}