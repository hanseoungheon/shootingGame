#pragma once

/*
* - �� ������ �ð� �Ի��� �ʿ��� �� ���
* - ��: 3�ʰ� �������� ���� Ȯ���� �� ���
* 
*/
class Timer
{
public:
	Timer(float targetTime = 0.0f);

	//�ʽð��� �ð��� �巯������ �ϱ� ���� �ʿ���
	void Tick(float deltaTime);

	//���� �Լ�
	void Reset();

	// ������ �ð��� ����ߴ��� Ȯ���ϴ� �Լ�
	bool IsTimeout() const;

	//Ÿ�̸� �ð� ���� �Լ�
	void SetTargetTime(float newTargetTime);

private:
	float elapsedTime = 0.0f;
	float targetTime = 0.0f;
};