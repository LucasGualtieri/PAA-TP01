#include "../include/progressBar.hpp"

using namespace std;

int main() {

	int n = 1000;

	for (int i = 0; i <= n; i++) {
		if ((i % (n / 100)) == 0) {
			this_thread::sleep_for(500ms);
			progressBar(i, 0, n);
			// cout << "i: " << i << endl;
		}
	}

	cout << "\nEnd of execution" << endl;
}
