#pragma once
#include <vector>
#include "Particle.h"

using namespace std;

class ObjectPool
{
	//'interleaved' node thingey
	struct __intern
	{
		bool open;
		size_t next;
		particle data;
	};

	__intern *m_data; //actual data array

	size_t m_size;
	size_t openHead, fillHead;

public:
	ObjectPool(size_t a_size) : m_size(a_size), openHead(0)
	{
		m_data = new __intern[m_size];

		for (size_t i = 0; i < m_size; i++)
		{
			m_data[i].open = true;
			m_data[i].next = i + 1;
		}
	}

	class iterator
	{
		ObjectPool *ref;
		size_t idx;

		iterator(ObjectPool *a_ref, size_t a_idx) : ref(a_ref), idx(a_idx) {}
	public:
		iterator() : ref(nullptr), idx(0) {}

		particle &operator* () { return ref->m_data[idx].data; }	//*this
		particle *operator->() { return &ref->m_data[idx].data; }	//this->

		const particle &operator* () const { return ref->m_data[idx].data; }	//*this
		const particle *operator->() const { return &ref->m_data[idx].data; }	//this->

		iterator &operator++() { idx = ref->m_data[idx].next; return *this; }		//++this
		iterator operator++(int) { auto that = *this; operator++(); return that; }	//this++

		bool operator==(const iterator & o) const { return ref == o.ref && idx == o.idx; }
		bool operator!=(const iterator &o) const { return !(*this == o); }

		operator bool() const { ref != nullptr && idx < ref->m_size && !ref->m_data[idx].open; }	//cast to boolean
	};


	iterator push(const particle &val)
	{
		//magic
		if (openHead >= m_size)
			return iterator();	//return null iterator

		size_t idx = openHead;

		m_data[idx].data = val;
		m_data[idx].open = false;

		openHead = m_data[openHead].next;

		

		size_t left = idx;
		while (m_data[--left].open);	//moves 'left' to the left until it hits an open node
		
		m_data[idx].next = m_data[left].next;
		m_data[left].next = idx;
	}

	iterator pop(const iterator &it)
	{

	}

};