// FranticDreamer 2022
#pragma once

#include <stdexcept>

namespace FranUtils
{

	// A Generic "Dynamic Array" container, similar to std::vector
	// The class is exportable to dlls, so you can easily use a dllexport macro
	template <class _T>
	class FranVector
	{
	private:
		_T* baseArrayData;
		size_t baseArraySize;

	public:
		FranVector();
		FranVector(const FranVector& _other);
		~FranVector();

		// ==========
		// Operators
		// ==========

		_T& operator[](size_t _index) const;

		void operator=(const FranVector<_T>& _other);

		bool operator==(const FranVector<_T>& _other);

		// ==========
		// Iterators
		// ==========

		_T* begin() { return &baseArrayData[0]; }
		const _T* begin() const { return &baseArrayData[0]; }
		_T* end() { return &baseArrayData[baseArraySize]; }
		const _T* end() const { return &baseArrayData[baseArraySize]; }

		// ==========
		// Modifier Functions
		// ==========

		// Add an element at the end of the Vector
		void Append(const _T& _objToAppend);

		// Add an element at a position into the Vector
		// Resize if the index is greater than size.
		void Insert(const _T& _objToInsert, size_t _position);

		// Remove an element at the end of the Vector
		void Pop() { PopIndex(baseArraySize - 1); };

		// Remove an element of the Vector
		void PopIndex(size_t _index);

		// Find element. Returns SIZE_MAX if not found
		size_t Find(const _T& _objToAppend);

		// Size of the vector AKA. Number of elements.
		size_t Size();

		// Resize the Vector
		// Removes elements from the end if new size is less than current size.
		// Adds elements with default constructor if new size is greater that current size.
		void Resize(size_t _newSize);

		// Clear the Vector
		void Clear();

		bool IsEmpty() const;

		// ==========
		// STL Vector Compatibility. Not Finished yet.
		// ==========
#ifdef FRANVECTOR_STL_COMP
		void push_back(const _T& _objToAppend) { Append(_objToAppend); };
		//void emplace_back(const _T& _objToAppend) { Append(_objToAppend); };

		_T& at(size_t _index) const { return operator[](_index); };
		_T& front() const { return operator[](0); };
		_T& back() const { return operator[](baseArraySize - 1); };

		bool empty() const { return IsEmpty(); };
#endif
	};

	// ==========
	// External Operators
	// ==========

	template <class _T>
	bool operator==(const FranVector<_T>& _a, const FranVector<_T>& _b)
	{
		return (_a == _b);
	}

	// ==========
	// External Iterators	
	// ==========

	template <class _T>
	_T* begin(FranVector<_T>& container) { return &container.begin(); };

	template <class _T>
	_T* begin(const FranVector<_T>& container) { return &container.begin(); };

	template <class _T>
	_T* end(FranVector<_T>& container) { return &container.end(); };

	template <class _T>
	const _T* end(const FranVector<_T>& container) { return &container.end(); };

};

// In case of a external linking
//#ifdef FRANUTILS_DYNAMIC

// =========
// Definitions
// =========

template <class _T>
FranUtils::FranVector<_T>::FranVector()
{
	baseArraySize = 0;
	baseArrayData = nullptr;
}

template <class _T>
FranUtils::FranVector<_T>::FranVector(const FranVector& _other)
{
	baseArraySize = 0;

	for (size_t i = 0; i < _other.baseArraySize; ++i)
		Append(_other.baseArrayData[i]);
}

template<class _T>
FranUtils::FranVector<_T>::~FranVector()
{
	delete[] baseArrayData;
}

template <class _T>
_T& FranUtils::FranVector<_T>::operator[](size_t _index) const
{
	if (_index >= baseArraySize)
		throw std::out_of_range("Subscript: Out Of Range!!");

	return baseArrayData[_index];
}

template <class _T>
void FranUtils::FranVector<_T>::operator=(const FranVector<_T>& _other)
{
	Clear();

	// TODO: Optimise
	for (size_t i = 0; i < _other.baseArraySize; ++i)
		Append(_other.baseArrayData[i]);
}

template<class _T>
bool FranUtils::FranVector<_T>::operator==(const FranVector<_T>& _other)
{
	if (baseArraySize != _other.baseArraySize)
		return false;

	for (size_t i = 0; i < baseArraySize; ++i)
		if (baseArrayData[i] != _other.baseArrayData[i])
			return false;

	return true;
}

template <class _T>
void FranUtils::FranVector<_T>::Append(const _T& _objToAppend)
{
	_T* tempArray = new _T[baseArraySize + 1]();

	// Copy old data into the new array
	for (size_t i = 0; i < baseArraySize; ++i)
		tempArray[i] = baseArrayData[i];

	// Add the last object, then increment base array size
	tempArray[baseArraySize++] = _objToAppend;

	// Remove old data
	delete[] baseArrayData;

	baseArrayData = tempArray;
}

template<class _T>
inline void FranUtils::FranVector<_T>::Insert(const _T& _objToInsert, size_t _position)
{
	if (_position > baseArraySize)
	{
		Resize(_position + 1);
		baseArrayData[_position] = _objToInsert;
		return;
	}

	_T* tempArray = new _T[baseArraySize + 1]();

	// Copy old data into the new array
	for (size_t i = 0; i < baseArraySize + 1; ++i)
		if (i >= _position)
			tempArray[i + 1] = baseArrayData[i];
		else
			tempArray[i] = baseArrayData[i];

	// Add the last object, then increment base array size
	tempArray[_position] = _objToInsert;
	baseArraySize++;

	// Remove old data
	delete[] baseArrayData;

	baseArrayData = tempArray;
}

template <class _T>
void FranUtils::FranVector<_T>::PopIndex(size_t _index)
{
	if (baseArraySize < 1 || _index >= baseArraySize)
		throw std::out_of_range("PopIndex: Out Of Range!!");

	_T* tempArray = new _T[baseArraySize - 1];

	// Copy old data into the new array
	for (size_t i = 0; i < baseArraySize - 1; ++i)
		if (i >= _index)
			tempArray[i] = baseArrayData[i + 1];
		else
			tempArray[i] = baseArrayData[i];

	// Remove old data
	delete[] baseArrayData;

	// Decrement array size
	baseArraySize--;

	baseArrayData = tempArray;
}

template <class _T>
size_t FranUtils::FranVector<_T>::Find(const _T& _objToAppend)
{
	for (size_t i = 0; i < baseArraySize; ++i)
	{
		if (baseArrayData[i] == _objToAppend)
			return i;
	}
	return SIZE_MAX;
}

template<class _T>
inline size_t FranUtils::FranVector<_T>::Size()
{
	return baseArraySize;
}

template<class _T>
inline void FranUtils::FranVector<_T>::Resize(size_t _newSize)
{
	_T* tempArray = new _T[_newSize]();

	// Copy old data into the new array
	for (size_t i = 0; i < std::min(_newSize, baseArraySize); ++i)
		tempArray[i] = baseArrayData[i];

	baseArraySize = _newSize;

	// Remove old data
	delete[] baseArrayData;

	baseArrayData = tempArray;
}

template <class _T>
void FranUtils::FranVector<_T>::Clear()
{
	// Remove old data
	if (baseArrayData)
	{
		delete[] baseArrayData;
		baseArrayData = nullptr;
	}

	baseArraySize = 0;
}

template<class _T>
bool FranUtils::FranVector<_T>::IsEmpty() const
{
	return baseArraySize == 0;
}

//#endif
