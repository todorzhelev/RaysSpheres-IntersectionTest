#include "Scene.h"

int main()
{
	Scene scene;
	scene.GenerateObjects();
	scene.CheckForIntersections();

	Sphere sphere(Vector3D(0, 0, 0), 1);
	Sphere sphere1(Vector3D(2, 2, 0), 1);

	Sphere res = BVH::GetBoundingSphere(sphere, sphere1);

	system("pause");
}