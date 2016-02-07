#include "Scene.h"
#include "BVH.h"

//NOTES:
//if we dont pass Vector3D by const reference we will get "formal parameter with requested alignment of 16 won't be aligned"
//m128 should be aligned to 16 bytes, otherwise it will crash
//m_direction should be normalized, otherwise the calculations will be wrong
//GetIntersection is not absolutely accurate

int main()
{
	Timer timer;

	Scene scene(&timer);

	scene.GenerateObjects();

	BVH bvh(&scene);

	scene.CheckForIntersections(&bvh);

	system("pause");
}