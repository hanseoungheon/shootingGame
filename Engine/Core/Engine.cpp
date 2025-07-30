#include <iostream>
#include "Engine.h"
#include "Level/Level.h"
#include <Windows.h>
#include "Utils/Utils.h"

//2���� �߰�
// ������
//�ܼ� �Է� ó�� ��Ʈ�ѷ�<Ű����>
//�ð����� Ÿ�̸�


Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
	switch (CtrlType)
	{
	case CTRL_CLOSE_EVENT:
		//Engine�� �޸� ����
		//Engine::Get().~Engine();
		Engine::Get().CleanUp();
		return false;
	}

	return false;
}

Engine::Engine()
{
	instance = this;

	//�ܼ� Ŀ�� ����


	//HANDLE
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info
	);

	//�ܼ�â �̺�Ʈ ���
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);

	//���� ���� �ε�
	LoadEngineSettings();
}

Engine::~Engine()
{
	CleanUp();
}

void Engine::Run()
{
	//�и� ������ ������ ���� �ð� �˷���
	//float currentTime = timeGetTime();

	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	//Windosw ī����
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	//�ϵ���� �ð������е�(���ļ� ��������)
	//���߿� �ʷ� ��ȯ�ϱ� ����
	LARGE_INTEGER freqeuncy;
	QueryPerformanceFrequency(&freqeuncy);

	//Ÿ�� ������
	float targetFramRate
		= (settings.framerate == 0.0f) ? 60.0f : settings.framerate;

	
	//Ÿ�� �� ������ �ð�
	float oneFrameTime = 1.0f / targetFramRate;

	while (true)
	{
		if (isQuit)
		{
			//���� ����
			break;
		}

		//������ �ð� ���
		//(���� �ð� - �����ð�) / ���ļ�
		QueryPerformanceCounter(&currentTime);


		//������ �ð�
		float deltaTime =
			(currentTime.QuadPart - previousTime.QuadPart)
			/ (float)freqeuncy.QuadPart;

		//�Է��� �ִ��� ����
		input.ProcessInput();

		//���� ������
		if (deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			////���� FPS ���
			//char title[50] = {};
			//sprintf_s(title, 50, "FPS: %f", (1.0f/deltaTime));
			////A�� �ܹ���, W�� w_char
			//SetConsoleTitleA(title);

			//�ð� ������Ʈ
			previousTime = currentTime;

			//���� �������� �Է��� ���
			input.SavePreviouseKeyStates();

			//���� �����ӿ� �߰� �� ���� ��û�� ���� ó��
			if (mainLevel)
			{
				mainLevel->ProcessAddAndDestroyActors();
			}
		}
	}

	//����
	//��� �ؽ�Ʈ ���� ������� ��������
	Utils::SetConsoleTextColor
	(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Engine::AddLevel(Level* newLevel)
{
	//������ �ִ� ������ ����
	if (mainLevel)
	{
		delete mainLevel;
	}

	mainLevel = newLevel;
}

void Engine::CleanUp()
{
	////���� ����
	//if (mainLevel)
	//{
	//	delete mainLevel;
	//	mainLevel = nullptr;
	//}
	SafeDelete(mainLevel);
}

void Engine::Quit()
{
	isQuit = true;
}

Engine& Engine::Get()
{
	return *instance;
}

int Engine::Width() const
{
	return settings.width;
}

int Engine::Height() const
{
	return settings.height;
}
void Engine::BeginPlay()
{
	if (mainLevel)
	{
		mainLevel->BeginPlay();
	}
}
void Engine::Tick(float deltaTime)
{
	//std::cout 
	//	<< "DeltaTime : " << deltaTime 
	//	<< ", FPS: "<< (1.0f/deltaTime)
	//	<< "\n";

	//if (GetKeyDown('A'))
	//{
	//	std::cout << "KeyDown\n";
	//}
	//if (GetKey('A'))
	//{
	//	std::cout << "Key\n";
	//}
	//if (GetKeyUp('A'))
	//{
	//	std::cout << "KeyUp\n";
	//}

	//���� ������Ʈ
	if (mainLevel)
	{
		mainLevel->Tick(deltaTime);
	}

	//if (GetKeyDown(VK_ESCAPE))
	//{
	//	Quit();
	//}
}

void Engine::Render()
{
	//SetConsoleTextAttribute(
	//	GetStdHandle(STD_OUTPUT_HANDLE),
	//	FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED // = 7
	//);

	Utils::SetConsoleTextColor
	(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	if (mainLevel)
	{
		mainLevel->Render();
	}
}

void Engine::LoadEngineSettings()
{
	//���� ���� ���� ����
	FILE* file = nullptr;
	fopen_s(&file, "../Settings/EngineSettings.txt", "rt");

	//������ ����
	if (file == nullptr)
	{
		std::cout << "Failed to load engine settings.\n";
		__debugbreak();
		return;
	}

	//�ε�

	//FP �����͸� ���� �ڷ� �ű��
	fseek(file, 0, SEEK_END);

	//�� ��ġ ���ϱ�
	size_t fileSize = ftell(file);

	// �ٽ� ù ��ġ�� �ǵ�����
	//fseek(file, 0, SEEK_SET); �̰� �ᵵ ��
	rewind(file);

	char* buffer = new char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);

	// ���� �б�
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);



	//���� �ؼ�(�Ľ�) => �ʿ��� ���� �ؼ�
	char* context = nullptr;
	char* token = nullptr;

	token = strtok_s(buffer, "\n",&context);

	while (token != nullptr)
	{
		// Ű/�� �и�
		char header[10] = { };

		//�Ʒ� ������ ����� �����Ϸ��� Ű�� �� ���̿� ��ĭ�� �־ ��.
		sscanf_s(token, "%s", header, 10);

		//��� ���ڿ� �� true 0 , false => �������� ũ�� ����, ������ ũ�� ���
		if (strcmp(header, "framerate") == 0)
		{
			sscanf_s(token, "framerate = %f", &settings.framerate);
		}
		else if (strcmp(header, "width") == 0)
		{
			sscanf_s(token, "width = %d", &settings.width);
		}
		else if(strcmp(header,"height") == 0)
		{
			sscanf_s(token, "height = %d", &settings.height);
		}


		token = strtok_s(nullptr, "\n", &context);
		//�� ���� �� �и�
	}

	//���� ����
	SafeDeleteArray(buffer);

	fclose(file);
}
