#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <type_traits>
#include <mutex>
#include <variant>

namespace gx_vessa
{
	template<typename T>
	class CustomVector
	{
	public:

		template<typename... Args>
		void multiple_push_back(Args&&... arg)
		{
			static_assert(
				(std::is_same_v<std::remove_cvref_t<Args>, T> && ...),
				"All arguments must have the same type as T."
			);
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

		T& operator[](int position)
		{
			return CustomVec[position];
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
			CustomVec.clear();
		}


	private:
		std::vector<T> CustomVec;


	};

	template<typename Key, typename Value>
	class Unorder_map
	{
	public:
		template<typename k, typename v>
		void insert(k&& key, v&& value)
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
		static void ranges(int times, std::function<void(const int index)> com)
		{
			for (int i = 0; i < times; i++)
			{
				com(i);
			}
		}
	};

	// A lock free counter using atomic and memory order which more effective than mutex
	class gx_counter
	{
	public:
		enum CountType
		{
			MAX = 1,
		};
		enum Value_State
		{
			FULL = 1,
			STILL = 0
		};
		template<typename MaxValue>
		gx_counter(const MaxValue value, Value_State vState)
			:
			vals{ vState }
		{
			if constexpr (std::is_same_v<MaxValue, int>)
			{
				if (value <= 0)
				{
					throw std::runtime_error{ "Value cannot be lower or equal zero" };
				}
				max_value.store(value);
			}
		}

		int get_value() const
		{
			return value_s.load(std::memory_order_acquire);
		}

		// Lock free increase function
		void inc(int by)
		{
			if (max_value.load() > 0)
			{
				int max = max_value.load();
				int current = value_s.load();

				while (true)
				{
					int desired = std::min(current + by, max);

					if (value_s.compare_exchange_weak(current, desired))
					{
						if (desired == max)
							vals = FULL;
						break;
					}
				}
			}
			else
			{
				value_s.fetch_add(by);
			}

			cv.notify_one();
		}

		Value_State GetState()
		{
			return vals.load(std::memory_order_acquire);
		}

		// Wait until your condition = true using conditional varible
		void Waitil_Predicate(std::function<bool(const std::atomic<Value_State>& state, const std::atomic<int>& value_inp)> predicate)
		{
			std::unique_lock lk{ mtx };
			auto f = [
				predicate = predicate,
				this
			]()
				{
					return predicate(vals, value_s);
				};

			cv.wait(lk, f);
		}

		void GetState_With_Condition(std::function<void(const Value_State state)> function)
		{
			function(vals.load(std::memory_order_acquire));
		}

		void Reset()
		{
			std::lock_guard<std::mutex> lk{ mtx };
			vals = STILL;
			max_value.store(0);
			value_s.store(0);
		}

	private:
		std::atomic<Value_State> vals;
		std::atomic<int> max_value{ 0 };
		std::condition_variable cv;
		std::mutex mtx;
		std::atomic<int> value_s{ 0 };
	};


}
