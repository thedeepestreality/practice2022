#include <iostream>
#include <chrono>
#include <thread>
#include "TSQueue.h"

int main(){
	using namespace std::chrono_literals;
	TSQueue<int> fifo;
	std::thread input_thread([&fifo]() {
		while (true) {
			int input;
			std::cin >> input;
			fifo.push(input);
		}
	});
	int counter = 1;
	auto start = std::chrono::high_resolution_clock::now();
	while(true){ 
		std::cout << ++counter << '\n';
		std::this_thread::sleep_for(1000ms);
		if (!fifo.empty()) {
			start = std::chrono::high_resolution_clock::now();
			int val = fifo.pop();
			std::cout << "user data: " << val << '\n';
		}
		// CIN IS NOT KILLABLE
		//else {
		//	const auto now = std::chrono::high_resolution_clock::now();
		//	const std::chrono::duration<double, std::milli> elapsed = now - start;
		//	if (elapsed.count() >= 3000) {
		//		input_thread.~thread();
		//		std::cout << "user input timeout\n";
		//	}
		//}
	}
	input_thread.join();
	return 0;
}