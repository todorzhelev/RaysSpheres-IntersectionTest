#include "Scene.h"
#include "BVH.h"
#include "Timer.h"

int main()
{
	Timer timer;

	Scene scene(&timer);

	scene.GenerateObjects();

	BVH bvh(&scene);

	scene.CheckForIntersections(&bvh);
	
	system("pause");
}