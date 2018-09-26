/* Ryan Harbert, rwharbert@mix.wvu.edu*/

#include "can_decoder.h"
using namespace std;

std::mutex mtx;

uint8_t can_data1[5] = {0x01,0x40,0x00,0x00,0x00};
uint8_t can_data2[5] = {0x06,0x40,0x00,0x00,0x00};
uint8_t can_data3[5] = {0x09,0x60,0x00,0x00,0x00};
uint8_t can_data4[5] = {0x0C,0x80,0x00,0x00,0x00};

void can_decode() {
	mtx.lock();
	int data;
	for (int i = 1; i < 5; ++i) {
		if (i == 1) {
			data = ((can_data1[0] << 8) | (can_data1[1]));
			data *= 0.03215;
		}
		if (i == 2) {
			data = ((can_data2[0] << 8) | (can_data2[1]));
			data *= 0.03215;
		}
		if (i == 3) {
			data = ((can_data3[0] << 8) | (can_data3[1]));
			data *= 0.03215;
		}
		if (i == 4) {
			data = ((can_data4[0] << 8) | (can_data4[1]));
			data *= 0.03215;
		}
		cout << "This is message " << i << ": " << data << endl;
	}
	mtx.unlock();
	return;
}

void can_update() {
	mtx.lock();
	int data;
	for (int i = 1; i < 5; ++i) {
		if (i == 1) {
			data = can_data1[1];
			data += 10;
			if (data == 255) {
				data = can_data1[0];
				data += 1;
				can_data1[0] = data;
				data = can_data1[1];
				data += 1;
				can_data1[1] = data;
			}
			else if (data > 255) {
				int temp = data - 255;
				data = can_data1[0];
				data += 1;
				can_data1[0] = data;
				data = can_data1[1];
				data = 0;
				data += temp;
				can_data1[1] = data;
			}
			else {
				can_data1[1] = data;
			}
		}
		if (i == 2) {
			data = can_data2[1];
			data += 10;
			if (data == 255) {
				data = can_data2[0];
				data += 1;
				can_data2[0] = data;
				data = can_data2[1];
				data += 1;
				can_data2[1] = data;
			}
			else if (data > 255) {
				int temp = data - 255;
				data = can_data2[0];
				data += 1;
				can_data2[0] = data;
				data = can_data2[1];
				data = 0;
				data += temp;
				can_data2[1] = data;
			}
			else {
				can_data2[1] = data;
			}
		}
		if (i == 3) {
			data = can_data3[1];
			data += 10;
			if (data == 255) {
				data = can_data3[0];
				data += 1;
				can_data3[0] = data;
				data = can_data3[1];
				data += 1;
				can_data3[1] = data;
			}
			else if (data > 255) {
				int temp = data - 255;
				data = can_data3[0];
				data += 1;
				can_data3[0] = data;
				data = can_data3[1];
				data = 0;
				data += temp;
				can_data3[1] = data;
			}
			else {
				can_data3[1] = data;
			}
		}
		if (i == 4) {
			data = can_data4[1];
			data += 10;
			if (data == 255) {
				data = can_data4[0];
				data += 1;
				can_data4[0] = data;
				data = can_data4[1];
				data += 1;
				can_data4[1] = data;
			}
			else if (data > 255) {
				int temp = data - 255;
				data = can_data4[0];
				data += 1;
				can_data4[0] = data;
				data = can_data4[1];
				data = 0;
				data += temp;
				can_data4[1] = data;
			}
			else {
				can_data4[1] = data;
			}
		}
	}
	mtx.unlock();
	return;
}

int main() {
	int num_threads;
	start:
	cout << "\e[44mHow many times do you want to decode and update?\e[0m" << endl;
	cout << "\e[44mEnter a number:\e[0m ";
	cin >> num_threads;
	if ((num_threads < 0) || (cin.fail())) {
		cin.clear();
		cin.ignore(999, '\n');
		cout << "\e[41mError: input is not valid! Please try again!!\e[0m" << endl;
		goto start;
	}
	std::vector<std::thread> thread_decode;
	std::vector<std::thread> thread_update;
	for (int i = 0; i < num_threads; ++i) {
		thread_decode.push_back(std::thread(can_decode));
		thread_update.push_back(std::thread(can_update));
	}
	for (auto &t : thread_decode) {
		t.join();
	}
	for (auto &t : thread_update) {
		t.join();
	}
	return 0;
}
