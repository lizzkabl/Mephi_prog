#pragma once
template<typename T>
concept is_ok = requires(T a, T b, int c) 
{
	a += b;
	a / c;
	a - b;
	a -= b;
	a * b;
};