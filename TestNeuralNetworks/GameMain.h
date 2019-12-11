#pragma once

constexpr const wchar_t* GAME_TITLE = L"�j���[�����l�b�g���[�N";        // �Q�[���^�C�g��

// <���>
constexpr const int SCREEN_WIDTH = 640;                  // ��ʂ̕�[pixel]
constexpr const int SCREEN_HEIGHT = 480;                  // ��ʂ̍���[pixel]

class Game
{
private:
	int lastX, lastY;
	std::vector<float> graph;
	std::vector<float> aigraph;

public:
	void Calculate();

	// �Q�[���̏���������
	void Initialize();

	// �Q�[���̍X�V����
	void Update();

	// �Q�[���̕`�揈��
	void Render();

	// �Q�[���̏I������
	void Finalize();
};
