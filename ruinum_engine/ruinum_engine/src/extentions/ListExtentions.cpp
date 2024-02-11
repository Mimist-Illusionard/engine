#ifndef LIST_EXTENTIONS_CPP
#define LIST_EXTENTIONS_CPP

#include "ListExtentions.h"

using namespace std;

template<typename T>
void RemoveElement(list<T> const& list, T element)
{
	for (T listElement : list)
	{
		if (listElement != element) continue;


	}
}

#endif