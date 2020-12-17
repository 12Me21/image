#include <stdio.h>
#include <chrono>
#include "timer.h++"

void timer(const char *message) {
	//ow
	using namespace std;
	using namespace chrono;
	static time_point<high_resolution_clock, nanoseconds> start {nanoseconds(-1)};
	if (start.time_since_epoch().count() < 0) {
		if (message)
			printf("%s",message);
		start = high_resolution_clock::now();
	} else {
		auto x = high_resolution_clock::now().time_since_epoch().count() - start.time_since_epoch().count();
		if (message)
			printf("%s",message);
		printf(" %.3fms\n", (float)x/1000000);
		start = (typeof(start))nanoseconds(-1);
	}
}
