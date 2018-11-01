#pragma once
#include <array>
#include <map>
#include <vector>


#define SIZE 32000
template<typename DATA, typename KEY, class HASH>

class hashtable
{
	HASH returnhash;
	std::array<std::map<KEY, DATA>, SIZE> table;
public:
	size_t index_for(KEY);
	void add(DATA, KEY);
	void erase(KEY);
	DATA operator [] (KEY);

	typename std::array<std::map<KEY, DATA>, SIZE>::iterator begin()
	{
		return table.begin();
	}

	typename std::array<std::map<KEY, DATA>, SIZE>::iterator end()
	{
		return table.end();
	}
};

template <typename DATA, typename KEY, class HASH>
size_t hashtable<DATA, KEY, HASH>::index_for(KEY key)
{
	return returnhash(key)&(SIZE - 1);
}

template <typename DATA, typename KEY, class HASH>
void hashtable<DATA, KEY, HASH>::add(DATA data, KEY key)
{
	table[index_for(key)][key] = data;
}

template <typename DATA, typename KEY, class HASH>
void hashtable<DATA, KEY, HASH>::erase(KEY key)
{
	(table[index_for(key)]).erase(key);
}

template <typename DATA, typename KEY, class HASH>
DATA hashtable<DATA, KEY, HASH>::operator[](KEY key)
{
	return table[index_for(key)][key];
}