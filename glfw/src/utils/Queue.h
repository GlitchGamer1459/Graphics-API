#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

namespace util {

	template<typename _Tp>
	class Queue {

	private:
		std::vector<_Tp> list;
		int length = 0;

	public:
		void Enqueue(_Tp item)
		{
			list.emplace_back(item);
			length++;
		}

		_Tp Dequeue()
		{
			_Tp item = list.front();
			list.erase(list.begin());
			length--;

			return item;
		}

		_Tp Peek()
		{
			return list.front();
		}

		bool IsEmpty()
		{
			return list.empty();
		}

		void Clear()
		{
			list.clear();
		}

		int len()
		{
			return length;
		}

	};

	void TestQueue()
	{
		util::Queue<int> queue;

		std::cout << "isempty: " << std::boolalpha << queue.IsEmpty() << std::endl;

		queue.Enqueue(1);
		queue.Enqueue(42);
		queue.Enqueue(-992);
		queue.Enqueue(64);
		queue.Enqueue(800003);
		queue.Enqueue(3);

		std::cout << "isempty: " << std::boolalpha << queue.IsEmpty() << std::endl;

		for (int i = 0, l = queue.len(); i < l; i++)
		{
			std::cout << "item: " << queue.Dequeue() << std::endl;
		}

		std::cout << "isempty: " << std::boolalpha << queue.IsEmpty() << std::endl;

		queue.Enqueue(1);
		queue.Enqueue(42);
		queue.Enqueue(-992);
		queue.Enqueue(64);
		queue.Enqueue(800003);
		queue.Enqueue(3);

		std::cout << "isempty: " << std::boolalpha << queue.IsEmpty() << std::endl;

		std::cout << "first item: " << queue.Peek() << std::endl;
		queue.Dequeue();
		std::cout << "first item: " << queue.Peek() << std::endl;

		queue.Clear();

		std::cout << "isempty: " << std::boolalpha << queue.IsEmpty() << std::endl;
	}

}