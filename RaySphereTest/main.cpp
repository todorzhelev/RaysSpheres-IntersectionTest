#include "Scene.h"

//if we dont pass Vector3D by const reference we will get "formal parameter with requested alignment of 16 won't be aligned"
//m128 should be pointer and we should align it. Otherwise it will crash
int main()
{
	Scene scene;
	scene.GenerateObjects();
	scene.CheckForIntersections();

	system("pause");
}