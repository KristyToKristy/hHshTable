#include<vector>
#pragma once
#include<iostream>
#include<string>
using namespace std;
template<class k,class v>
struct HashTableNode
{
	k _key;
	v _value;
	HashTableNode<k,v>* _next;
	HashTableNode(const k& key,const v& value)
		:_key(key)
		,_value(value)
		,_next(NULL)
	{}
};
template<class k>
struct __HashFunc
{
	size_t operator() (const k&key)
	{
		return key;
	}
};
template<>
struct __HashFunc<string>
{
	size_t operator()(const string& key)
	{
		size_t hash = 0;
        for(size_t i=0;i<key.size();++i)
		{
			hash += key[i];
		}
		return hash;
	}
};
template <class k,class v,class HashFunc = __HashFunc<k> >
class HashTable
{
public:
	HashTable()
		:_table(NULL)
		,_size(0)
	{}
	HashTable(size_t capacity)
		:_size(0)
	{
		_table.resize(_CheckCapacity());
	}
	~HashTable()
	{
		for(size_t i=0;i<_table.size();++i)
		{
			HashTableNode<k,v>* cur = _table[i];//_table[i]重命名为cur
			while(cur)
			{
				HashTableNode<k,v>* del = cur;
				cur = cur->_next ;     //每次使cur为它的下一个
				delete del;
			}
			_table[i] = NULL;
		}
	}
	HashTable(const HashTable<k,v> & ht)
		:_size(0)
	{
		_table.resize(ht._table.size());
		for(size_t i = 0;i<ht._table.size();++i)
		{
			HashTableNode<k,v>* cur = ht._table[i];
			while(cur)
			{
				Insert(cur->_key ,cur->_value);
				cur = cur->_next ;
			}
		}
	}
	//赋值
	HashTable<k,v>  &operator = ( HashTable<k,v>& ht )
	{
		if(this != &ht)
		{
			HashTable<k,v> tmp(ht);
			_table.swap(tmp._table);
			swap(_size,tmp._size);
		}
		return *this;
	}
public:
	bool Insert(const k& key,const v& value)
	{
		_CheckCapacity();
		size_t index = _HashFunc(key,_table.size());
		HashTableNode<k,v>* cur = _table[index];
		while(cur)
		{
			if(cur->_key == key)
			{
				return false;
			}
			cur = cur->_next ;
		}
		HashTableNode<k,v>* tmp = new HashTableNode<k,v> (key,value);
		tmp->_next = _table[index];
		_table[index] = tmp;
		++_size;
		return true;
	}
	HashTableNode<k,v>* Find(const k& key)
	{
		size_t index = _HashFunc(key,_table.size());
		HashTableNode<k,v>* cur = _table[index];
		while(cur)
		{
			if(cur->_key == key)
			{
				return cur;
			}
			cur = cur->_next ;
		}
		return NULL;
	}
	bool Remove(const k& key)
	{
		size_t index = _HashFunc(key,_table.size());
		HashTableNode<k,v>* cur = _table[index];
		HashTableNode<k,v>* prev = NULL;
		HashTableNode<k,v>* del = NULL;
		if(cur->_key == key)
		{
			del = cur;
			_table[index] = cur->_next ;
			delete del;
			return true;
		}
		prev = cur;
		cur = cur->_next ;
		while(cur)
		{
			if(cur->_key == key)
			{
				del = cur;
				prev->_next = cur->_next ;
				delete del;
				return true;
			}
			prev = cur;
			cur = cur->_next ;
		}
		return false;
	}
	void Print()
	{
		for(size_t i = 0;i<_table.size();++i)
		{
			printf("_table[%d]:",i);
			HashTableNode<k,v>* cur = _table[i];
			while(cur)
			{
				cout<<"["<<cur->_key <<","<<cur->_value <<"]"<<"->";
				cur = cur->_next ;
			}
			cout<<"NULL"<<endl;
		}
	}
protected:
	size_t _HashFunc(const k& key,size_t capacity)
	{
		HashFunc  hash;
		return hash(key) % capacity;
	}
	size_t _GetNetPrime(const size_t size)
	{
	    const int _PrimeSize = 28;
        static const unsigned long _PrimeList [_PrimeSize] =
        {
            53ul,         97ul,         193ul,       389ul,       769ul,
 
            1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
 
            49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
 
            1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
 
            50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
 
            1610612741ul, 3221225473ul, 4294967291ul
        };
		for(size_t i = 0;i<_PrimeSize ;++i)
		{
			if(_PrimeList[i]>_size)
			{
				return _PrimeList[i];
			}
		}
		return _PrimeList[_PrimeSize - 1];
	}

	void _CheckCapacity()
	{
		if(_size == _table.size())
		{
			size_t nextPrime = _GetNetPrime(_size);
			vector<HashTableNode<k,v>* > nextTable;
			nextTable.resize(nextPrime);
			for(size_t i=0;i<_table.size();++i)
			{
				HashTableNode<k,v>* cur = _table[i];
				while(cur)
				{
					HashTableNode<k,v>* tmp = cur;
					cur = cur->_next;
					//在新表中相应的位置，头插
					size_t index = _HashFunc(tmp->_key ,nextPrime);
					nextTable[index] = tmp;
				}
				_table[i] = NULL; 
			}
			_table.swap(nextTable);
		}
	}
protected:
	vector <HashTableNode<k,v>* > _table;
	size_t _size;
};
