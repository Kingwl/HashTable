#pragma once
template<typename T> class HashKey{
public:
	static enum  State
	{
		none = 0,
		used = 1,
		unused = 2
	};
	HashKey(){
		_next = nullptr;
		_state = State::none;
	}
	~HashKey(){
		if (_next != nullptr)
			delete _next;
	};
	void SetValue(T value)
	{
		_data = value;
		_state = used;
	}
	T _data;
	HashKey<T> *_next;
	State _state;
};
template<typename T, int SIZE = 100> class HashTable
{
public:
	HashTable(){ init(); };
	~HashTable(){
		shutdown();
	};
	void init()
	{
		for (int i = 0; i < SIZE; i++)
		{
			_elemts[i] = new HashKey<T>();
		}
	}
	void clear()
	{
		shutdown();
		init();
	}
	int getHash(const T &value)
	{
		return value;
	}
	void addKey(const T &value)
	{
		int key = getHash(value) % SIZE;
		HashKey<T> *p = _elemts[key];
		while (p != nullptr)
		{
			if (p -> _state == HashKey<T>::State::used)
			{
				if (p -> _next == nullptr)
				{
					p -> _next = new HashKey<T>();
				}
				p = p -> _next;
			}
			else
			{
				p -> SetValue(value);
				return;
			}
		}
	}
	bool findKey(const T &value)
	{
		int key = getHash(value) % SIZE;
		HashKey<T> *p = _elemts[key];
		while (p != nullptr)
		{
			if (p -> _state == HashKey<T>::State::used && p -> _data == value)
			{
				return true;
			}
			p = p -> _next;
		}
		return false;
	}
	bool deleteKey(const T &value)
	{
		int key = getHash(value) % SIZE;
		HashKey<T> *p = _elemts[key];
		while (p != nullptr)
		{
			if (p -> _state == HashKey<T>::State::used && p -> _data == value)
			{
				p -> _state = HashKey<T>::State::unused;
				return true;
			}
		}
		return false;
	}
private:
	void shutdown()
	{
		for (int i = 0; i < SIZE; i++)
		{
			delete _elemts[i];
		}
	}
	HashKey<T> *_elemts[SIZE];
};

