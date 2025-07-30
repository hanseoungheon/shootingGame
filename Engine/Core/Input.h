#pragma once

#include "Core.h"

class Engine_API Input
{
	friend class Engine;

	//Ű�Է� Ȯ���� ���� ����ü ����
	struct KeyState
	{
		//���� �����ӿ� Ű�� ���ȴ��� ����
		bool isKeyDown = false;

		//���� �����ӿ� Ű�� ���ȴ��� ����
		bool previouseKeyDown = false;
	};

public:
	Input();

	//Ű Ȯ�� �Լ�
	bool GetKey(int KeyCode);
	bool GetKeyDown(int KeyCode);
	bool GetKeyUp(int KeyCode);


	static Input& Get();
private:
	void ProcessInput();
	void SavePreviouseKeyStates();

	//Ű �Է� ���� ���� ����
	KeyState keyStates[255] = { };

	static Input* instance;
};