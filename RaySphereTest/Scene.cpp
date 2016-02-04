#include "Scene.h"

void Scene::GenerateObjects()
{
	int numberOfRays = GetRG()->GetRandomInt(0, 3);
	int numberOfSpheres = GetRG()->GetRandomInt(0, 2000);

	for (int i = 0; i < numberOfRays; i++)
	{
		Vector3D pos = GetRG()->GetRandomPosition(0, 10000);
		Vector3D dir = GetRG()->GetRandomPosition(0, 10000);

		Ray ray(pos, dir);

		rays.push_back(ray);
	}

	for (int i = 0; i < numberOfSpheres; i++)
	{
		Vector3D pos = GetRG()->GetRandomPosition(0, 10000);
		float radius = GetRG()->GetRandomFloat(0, 1);

		Sphere sphere(pos, radius);

		spheres.push_back(sphere);
	}
}

void Scene::CheckForIntersections()
{
	int intersectionsAmount = 0;

	for (int i = 0; i < rays.size(); i++)
	{
		for (int j = 0; j < spheres.size(); j++)
		{
			Vector3D resultPoint(0, 0, 0);
			bool intersect = IntersectRaySphere(rays[i], spheres[j], resultPoint);

			if (intersect)
			{
				std::cout << intersectionsAmount << " Intersection point: " << resultPoint << std::endl;

				intersectionsAmount++;
			}
		}
	}
}

bool Scene::IntersectRaySphere(Ray& ray, Sphere& sphere, Vector3D& intersectionPoint)
{
	Vector3D m = ray.m_startPos - sphere.m_centerPosition;
	float b = DotProduct(m, ray.m_direction);
	float c = DotProduct(m, m) - sphere.m_radius * sphere.m_radius;

	// Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)
	if (c > 0.0f && b > 0.0f)
	{
		return false;
	}

	float discr = b*b - c;

	// A negative discriminant corresponds to ray missing sphere
	if (discr < 0.0f)
	{
		return false;
	}

	// Ray now found to intersect sphere, compute smallest t value of intersection
	float t = -b - sqrt(discr);

	// If t is negative, ray started inside sphere so clamp t to zero
	if (t < 0.0f) t = 0.0f;
	intersectionPoint = ray.m_startPos + t * ray.m_direction;

	return true;
}