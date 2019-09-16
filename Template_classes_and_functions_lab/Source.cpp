#include <iostream>
#include <string>
#include <limits>
#include <type_traits>


auto max = std::numeric_limits<int>::min();

template <typename T> struct is_int;

template <typename T> struct is_int {
	static const bool val = false;
};
template <> struct is_int<int> {
	static const bool val = true;
};

template <bool, typename T> struct KStruct;

template <typename T> struct KStruct<false, T> {
	static auto GetValue(T x) {
		return std::numeric_limits<int>::min();
	}
};
template <typename T> struct KStruct<true, T> {
	static int GetValue(T x) {
			return x;
	}
};

template <typename T1, typename T2, typename ...Args> auto task_func(T1 x1, T2 x2, Args...args);
template <typename T1, typename T2> auto task_func(T1 x1, T2 x2);
template <typename T1> auto task_func(T1 x);


template <typename T1, typename T2, typename ...Args> auto task_func(T1 x1, T2 x2, Args...args)
{	
	int maxy,value;
	maxy = task_func<Args...>(args...);
	value = KStruct<is_int<T2>::val, T2>::GetValue(x2);
	if (maxy < value)maxy = value;
	return maxy;
}

template <typename T1, typename T2> auto task_func(T1 x1, T2 x2)
{	
	int value;
	value = KStruct<is_int<T2>::val, T2>::GetValue(x2);
	return value;
}
template <typename T1> auto task_func(T1 x)
{
	return std::numeric_limits<int>::min();
}
auto task_func() {
	return std::numeric_limits<int>::min();
}

int main() {
	setlocale(LC_ALL, "Russian");
 	int m = task_func(2);
	if (m == std::numeric_limits<int>::min())
		std::cout << "Минимального int на чётной позиции нет!!!";
	else 
		std::cout << m << std::endl;
	system("pause");
	return 0;
}