#include "Scene.h"
#include "BVH.h"

//NOTES:
//if we dont pass Vector3D by const reference we will get "formal parameter with requested alignment of 16 won't be aligned"
//m128 should be aligned to 16 bytes, otherwise it will crash
//m_direction should be normalized, otherwise the calculations will be wrong
//GetIntersection is not absolutely accurate
int main()
{
	Scene scene;
	scene.GenerateObjects();

	std::cout << "Press 0 for closest intersection point for first sphere" << std::endl;
	std::cout << "Press 1 for closest intersection point with all spheres" << std::endl;

	int choice;
	std::cin >> choice;

	BVH bvh(&scene);

	scene.CheckForIntersections((bool) choice);

	system("pause");
}