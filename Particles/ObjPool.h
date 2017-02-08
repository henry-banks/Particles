#pragma once

using namespace std;

template<typename T>
class ObjectPool
{
	//'interleaved' node thingey
	struct __intern
	{
		bool open;
		size_t next;
		T data;
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

		//???
		friend class ObjectPool;

		iterator(ObjectPool *a_ref, size_t a_idx) : ref(a_ref), idx(a_idx) {}
	public:
		iterator() : ref(nullptr), idx(0) {}

		T &operator* () { return ref->m_data[idx].data; }	//*this
		T *operator->() { return &ref->m_data[idx].data; }	//this->
		T *operator& () { return &ref->m_data[idx].data; } //&this

		const T &operator* () const { return ref->m_data[idx].data; }	//*this
		const T *operator->() const { return &ref->m_data[idx].data; }	//this->
		const T *operator& () const { return &ref->m_data[idx].data; } //&this

		iterator &operator++() { idx = ref->m_data[idx].next; return *this; }		//++this
		iterator operator++(int) { auto that = *this; operator++(); return that; }	//this++

		bool operator==(const iterator & o) const { return ref == o.ref && idx == o.idx; }
		bool operator!=(const iterator &o) const { return !(*this == o); }

		operator bool() const { ref != nullptr && idx < ref->m_size && !ref->m_data[idx].open; }	//cast to boolean

		operator T*() { return operator&(); }
		operator const T*() const { return operator&(); }

		//Adress-of operator (???)
		iterator &free() { return *this = ref->pop(*this); }
	};


	iterator push(const T &val = T())
	{
		//magic, all magic

		if (openHead >= m_size)
			return iterator();	//return null iterator

		size_t idx = openHead;

		m_data[idx].data = val;
		m_data[idx].open = false;

		openHead = m_data[openHead].next;

		if (idx < fillHead) //if we get inserted before the head, become head
		{
			m_data[idx].next = fillHead;
			fillHead = idx;
		}
		else //otherwise ther eMUST be something filled to our left
		{
			size_t left = idx;
			while (m_data[--left].open);	//moves 'left' to the left until it hits an open node

			m_data[idx].next = m_data[left].next;
			m_data[left].next = idx;
		}		
		return iterator(this, idx);
	}

	iterator pop(iterator it)
	{
		if (!(it && it.ref == this)) return iterator();

		size_t idx2 = it.idx;
		it++;

		// if we are popping the closed head, we need to update the close list
		// if we are popping left of the vacant head, we need to update the vacant head
		// if there was a closed next pointing to this index, we have to update it.
		m_data[idx2].open = true;

		// For fixing the filled list pointers
		if (idx2 == fillHead)
			fillHead = m_data[idx2].next;
		else //there must be a closed index pointing to us.
		{
			size_t left = idx2;
			while (m_data[--left].open); //go left until we hit the thing pointing at us
			m_data[left].next = m_data[idx2].next;
		}

		// For inserting the open space
		if (idx2 < openHead)
		{
			if (idx2 < openHead)
			{
				m_data[idx2].next = openHead;
				openHead = idx2;
			}
			else //If there is a vacancy to our left...
			{
				size_t left = idx2;
				while (!m_data[--left].open); //see above

				m_data[idx2].next = m_data[left].next;
				m_data[left].next = idx2;
			}
			return it;
		}
	}

	//used in for loops
	iterator begin() { return iterator(this, fillHead); }
	iterator end() { return iterator(this, m_size); }

	//e.g. for(auto it = begin(); it != end(); ++it);
};