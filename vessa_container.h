#include <iostream>
#include <vector>
#include <functional>

namespace gx_vessa
{
	template<typename T>
	class CustomVector
	{
	public:
		
		template<typename... Args>
		void multiple_push_back(Args&&... arg)
		{
			(CustomVec.push_back(std::forward<Args>(arg)), ...);
		}
		size_t GetSize()
		{
			return CustomVec.size();
		}
		void for_each(std::function<void(const T element, const int at)> function)
		{
			int index = 0;
			for (auto& elements : CustomVec)
			{
				function(elements, index);
				index++;
			}
			
		}
		
		void Multiple_PopBack(int times)
		{
			for (int i = 0; i < times; i++)
			{
				CustomVec.pop_back();
			}
		}

		void Zero_memory() const
		{
			CustomVec.empty();
		}

			
	private:
		std::vector<T> CustomVec;
	

	};

	template<typename Key, typename Value>
	class Unorder_map
	{
	public:
		template<typename k, typename v>
		void insert(k&& key,v&& value)
		{
			key_collecter.push_back(std::forward<k>(key));
			value_collecter.push_back(std::forward<v>(value));
		}
		Value& get_value(const Key& key)
		{
			
			for (int i = 0; i < key_collecter.size(); i++)
			{
				if (key_collecter[i] == key)
				{
					return value_collecter[i];
				}
			}
			// Out of range 
			throw std::out_of_range("Key not found");

		}
		Value& operator[](const Key& key)
		{
			for (int i = 0; i < key_collecter.size(); i++)
			{
				if (key_collecter[i] == key)
				{
					return value_collecter[i];
				}
			}
			// Out of range 
			throw std::out_of_range("Key not found");
		}

		void for_each_values(std::function<void(const Value& value, const int at)> function)
		{
			int index = 0;
			for (auto& val : value_collecter)
			{
				function(val, index);
				index++;
			}
		}
	private:
		std::vector<Key> key_collecter;
		std::vector<Value> value_collecter;
	};

	class gx_print
	{
	public:
		template<typename... Args>
		static void print(Args... args)
		{
			((std::cout << args), ...);
		}
	};

	class iota
	{
	public:
		static void ranges(int times, std::function<void( const int index )> com)
		{
			for (int i = 0; i < times; i++)
			{
				com(i);
			}
		}
	};
	
}
