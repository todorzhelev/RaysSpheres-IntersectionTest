#include "Scene.h"
#include "BVH.h"


//NOTES:
//if we dont pass Vector3D by const reference we will get "formal parameter with requested alignment of 16 won't be aligned"
//m128 should be aligned to 16 bytes, otherwise it will crash
//m_direction should be normalized, otherwise the calculations will be wrong
//GetIntersection is not absolutely accurate
//probably everything should be data oriented. This should fix the problem with the alignments and the expand of boungind spheres
//the index of a node is missing and also the index of the child is wrongly calculated
//if the BVH is tested first and then the regular method, the BVH is 2 or 3 times slower. If the regular method is tested first, the two methods are close to each other.
//but still the BVH is slower. 
//why am i comparing times in Debug??
//maxObjectsInLeaf should be bigger
int main()
{
	for (int i = 0; i < 10; i++)
	{
		Timer timer;

		Scene scene(&timer);

		scene.GenerateObjects();

		BVH bvh(&scene);

		scene.CheckForIntersections(&bvh);
	}
	
	system("pause");
}