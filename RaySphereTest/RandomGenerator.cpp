#include "RandomGenerator.h"

RandomGenerator* RandomGenerator::randomGenerator = nullptr;

RandomGenerator::RandomGenerator()
{
	std::random_device randDevice;
	auto seed_val = randDevice();

	m_randEngine.seed(seed_val);
}

Vector3D RandomGenerator::GetRandomPosition(float min, float max)
{
	std::uniform_real_distribution < float > distr(min, max);

	float x = distr(m_randEngine);
	float y = distr(m_randEngine);
	float z = distr(m_randEngine);

	return Vector3D(x, y, z);
}

float RandomGenerator::GetRandomFloat(float min, float max)
{
	std::uniform_real_distribution < float > distr(min, max);

	float num = distr(m_randEngine);
	return num;
}

int RandomGenerator::GetRandomInt(int min, int max)
{
	std::uniform_int_distribution < int > distr(min, max);

	float num = distr(m_randEngine);
	return num;
}
