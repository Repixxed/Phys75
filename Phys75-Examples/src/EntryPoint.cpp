#include <misc/Allocator.h>

#include <iostream>

struct Test
{
	int x, y;
};

int main()
{
	Phys75::Allocator::alloc_pool<Test>(10);

	Phys75::Ref<Test> test = Phys75::Allocator::alloc_resource<Test>(10, 20);

	std::cout << test.get()->x << " " << test.get()->y << std::endl;
}