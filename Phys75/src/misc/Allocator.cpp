#include "Allocator.h"

namespace Phys75 {

	std::unordered_map<std::type_index, MemoryBlock> Allocator::m_Blocks;

}