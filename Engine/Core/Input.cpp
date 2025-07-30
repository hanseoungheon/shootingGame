#include "Input.h"
#include <Windows.h>

//static ���� ����
Input* Input::instance = nullptr;

Input::Input()
{
	//�̱��� ������ ���� this Ű���� ���!
	instance = this;
}
void Input::ProcessInput()
{
	//Ű �Է� Ȯ��
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].isKeyDown
			= GetAsyncKeyState(ix) && 0x8000;
	}
}

void Input::SavePreviouseKeyStates()
{
	//���� �������� �Է��� ���
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].previouseKeyDown
			= keyStates[ix].isKeyDown;
	}
}

bool Input::GetKey(int KeyCode)
{
	//auto& instance =Engine().
	return keyStates[KeyCode].isKeyDown;

}

bool Input::GetKeyDown(int KeyCode)
{
	return !keyStates[KeyCode].previouseKeyDown
		&& keyStates[KeyCode].isKeyDown;
}

bool Input::GetKeyUp(int KeyCode)
{
	return keyStates[KeyCode].previouseKeyDown
		&& !keyStates[KeyCode].isKeyDown;
}

Input& Input::Get()
{
	return *instance;
}