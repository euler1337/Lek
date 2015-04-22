
#ifndef __STORAGE_H
#define __STORAGE_H

template <typename T>
class storage {
public:
	storage<T>::storage(unsigned int size) :
	m_size(size),
	m_elements(new T[size]) {

	};

	unsigned int size(void) const {
		return m_size;
	};

private:
	unsigned int m_size;
	T* m_elements;
};

#endif