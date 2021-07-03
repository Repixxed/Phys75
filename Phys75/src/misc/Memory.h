#pragma once

#include <memory>
#include <assert.h>
#include <typeindex>
#include <unordered_map>

#include <set>

namespace Phys75 {

	template<typename T, typename... Args>
	struct Ref
	{
		Ref(Args&&... args);
		~Ref();

		Ref(T* data);

		Ref(const Ref<T, Args...>& other);
		Ref<T, Args...> operator=(const Ref<T, Args...>& other);

		T* get();

	private:
		T* m_Memory;
		size_t* m_Counter;
		bool m_Delete;
	};

	struct MemoryBlock
	{
		friend class Allocator;

		MemoryBlock(size_t increase = 1);
		~MemoryBlock();

		void set_increase(size_t increase);

		template<typename T>
		void alloc();

		template<typename T>
		T* get(size_t index);

		template<typename T>
		T* next();

		void mark_free(size_t index);
		size_t get_size();
	
	private:

		void* m_Begin = nullptr;
		
		size_t m_Iterator = 0;
		size_t m_Size = 0;
		size_t m_SizeIncrease = 0;

		std::set<size_t> m_Free;
	};

	class Allocator
	{
	public: 
		
		template<typename T, typename... Args>
		static Ref<T> alloc_resource(Args&&... args);

		template<typename T>
		static void alloc_pool(size_t max);

		template<typename T>
		static void mark_dirty(T* data);

	private:

		static std::unordered_map<std::type_index, MemoryBlock> m_Blocks;
	};

	//----------------------------------------------------------------------------------


	//Ref-------------------------------------------------------------------------------

	template<typename T, typename... Args>
	inline Ref<T, Args...>::Ref(Args&& ...args)
	{
		m_Counter = new size_t(1);
		m_Memory = new T(args...);
		m_Delete = true;
	}

	template<typename T, typename... Args>
	inline Ref<T, Args...>::~Ref()
	{
		(*m_Counter)--;

		if (*m_Counter == 0)
		{
			if (m_Delete)
				delete m_Memory;
			else
				Allocator::mark_dirty(m_Memory);
		}
	}

	template<typename T, typename... Args>
	inline Ref<T, Args...>::Ref(T* data)
	{
		m_Counter = new size_t(0);
		(*m_Counter)++;
		m_Memory = data;
		m_Delete = false;
	}

	template<typename T, typename... Args>
	inline Ref<T, Args...>::Ref(const Ref<T, Args...>& other)
	{
		m_Counter = other.m_Counter;
		(*m_Counter)++;
		m_Memory = other.m_Memory;
		m_Delete = other.m_Delete;
	}

	template<typename T, typename... Args>
	inline Ref<T, Args...> Ref<T, Args...>::operator=(const Ref<T, Args...>& other)
	{
		m_Counter = other.m_Counter;
		(*m_Counter)++;
		m_Memory = other.m_Memory;
		m_Delete = other.m_Delete;
		return *this;
	}

	template<typename T, typename ...Args>
	inline T* Ref<T, Args...>::get()
	{
		return m_Memory;
	}

	//-------------------------------------------------------------------------------------


	//Allocator----------------------------------------------------------------------------

	template<typename T, typename... Args>
	inline Ref<T> Allocator::alloc_resource(Args&&... args)
	{
		*m_Blocks[typeid(T)].next<T>() = T{ args... };
		size_t it = m_Blocks[typeid(T)].m_Iterator;
		return Ref<T>(m_Blocks[typeid(T)].get<T>(it));
	}

	template<typename T>
	inline void Allocator::alloc_pool(size_t max)
	{
		m_Blocks[typeid(T)].set_increase(max);
		m_Blocks[typeid(T)].alloc<T>();
	}

	template<typename T>
	inline void Allocator::mark_dirty(T* data)
	{
		std::ptrdiff_t ptr = data - static_cast<T*>(m_Blocks[typeid(T)].m_Begin);
		m_Blocks[typeid(T)].mark_free((size_t)ptr);
	}

	//-----------------------------------------------------------------------------------

	inline MemoryBlock::MemoryBlock(size_t increase)
	{
		set_increase(increase);
	}

	inline MemoryBlock::~MemoryBlock()
	{
		delete[] m_Begin;
	}

	inline void MemoryBlock::set_increase(size_t increase)
	{
		if (increase <= 0) increase = 1;
		m_SizeIncrease = increase;
	}

	template<typename T>
	inline void MemoryBlock::alloc()
	{
		m_Size += m_SizeIncrease;
		m_Begin = new T[m_Size];
	}

	template<typename T>
	inline T* MemoryBlock::get(size_t index)
	{
		return &static_cast<T*>(m_Begin)[index];
	}

	inline void MemoryBlock::mark_free(size_t index)
	{
		m_Free.insert(index);
	}

	inline size_t MemoryBlock::get_size()
	{
		return m_Size;
	}

	template<typename T>
	inline T* MemoryBlock::next()
	{
		if (!m_Free.empty())
		{
			T* next = &static_cast<T*>(m_Begin)[*m_Free.begin()];
			m_Free.erase(m_Free.begin());
			return next;
		}

		if (m_Iterator == m_Size - 1)
		{
			assert(m_SizeIncrease >= 1);

			m_Size += m_SizeIncrease;
			m_Begin = std::realloc(m_Begin, m_Size);
			m_Iterator = m_Size - m_SizeIncrease;
		}
		else
		{
			m_Iterator++;
		}

		return &static_cast<T*>(m_Begin)[m_Iterator];
	}

	//----------------------------------------------------------------------------
}
