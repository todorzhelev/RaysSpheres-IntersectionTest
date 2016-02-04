#pragma once
#include<random>
#include"Vector3D.h"

class RandomGenerator
{
public:

	RandomGenerator();
	Vector3D GetRandomPosition(float min, float max);
	float GetRandomFloat(float min, float max);
	int GetRandomInt(int min, int max);

	static RandomGenerator* GetRandomGenerator()
	{
		if (randomGenerator == nullptr)
		{
			randomGenerator = new RandomGenerator;
			return randomGenerator;
		}

		return randomGenerator;
	}

private:
	static RandomGenerator* randomGenerator;

	std::mt19937 m_randEngine;
};

inline RandomGenerator* GetRG()
{
	return RandomGenerator::GetRandomGenerator();
}



