#include "pch.h"
#include "GameMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ���g�p�����̌x���΍�
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);


	// �f�o�b�O���p���O�t�@�C���̏o�̗͂}��
	SetOutApplicationLogValidFlag(FALSE);


	// �N�����[�h�̐ݒ�
#if defined(_DEBUG)
	ChangeWindowMode(TRUE);	          // �E�C���h�E���[�h�Ŏ��s
	SetMainWindowText(GAME_TITLE);    // �E�C���h�E�^�C�g���̐ݒ�
	//SetWindowIconID(IDI_ICON1);       // �E�C���h�E�A�C�R���̐ݒ�
#else
	ChangeWindowMode(FALSE);	      // �t���X�N���[���Ŏ��s
#endif


	// ������Ԃ̉�ʃ��[�h�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);


	// DX���C�u�����̏���������
	if (DxLib_Init() == -1)
	{
		return -1;    // �G���[���N�����璼���ɏI��
	}


	// �`���𗠉�ʂɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	Game game;

	// �Q�[���̏���
	game.Initialize();    // �Q�[���̏���������

	while (!ProcessMessage() && !CheckHitKey(EXIT_KEY))
	{
		game.Update();          // �Q�[���̍X�V����
		game.Render();          // �Q�[���̕`�揈��

		ScreenFlip();          // ����ʂ̓��e��\��ʂɔ��f
		ClearDrawScreen();     // ����ʂ̏���
	}

	game.Finalize();      // �Q�[���̏I������


	// DX���C�u�����̏I������
	DxLib_End();


	return 0;    // ����I��
}
