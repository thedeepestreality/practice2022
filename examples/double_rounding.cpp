#include <iostream>

int main()
{
	std::cout.precision(32);
	std::cout << (0.1 == (1.1 - 1)) << '\n';
	std::cout << 0.1 << ' ' << 1.1 << ' ' << 1.1 - 1 << '\n';
	return 0;
}