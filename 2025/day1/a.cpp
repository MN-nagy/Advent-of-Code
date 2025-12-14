#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

#define INPUT "input.txt"
#define TEST_INPUT "testinput.txt"


/*
- Lines represent sequance of rotations
- Each starts with "L" or "R", "L" => indicates decrese & "R" -> indicates Increase
- the "distance" indicates how many rotations should happen

so

R or L + distance (E.g: L19 , R8)

if on 1 and got R8 => 9

- No negative numbers (> 0) will result it max value (aka: 99) and same for (< 99) results in 0
- The password is the number of 0 encoutered

- For now the dial points at 50
*/


vector<string> parseFile(const string &filename);
tuple<string, int> directionDist(const string &code);



int main(void) {
	vector<string> rotationSeq = parseFile(INPUT); // size is 4777
	int rotations = 50;
	size_t total = 0;

	for (const auto& code : rotationSeq) {
		auto [direction, distance] = directionDist(code);
		if (direction == "R") {
			rotations = (rotations + distance) % 100;
		} else {
			rotations = (rotations - distance) % 100;
			if (rotations < 0)  rotations += 100;
		}

		if (rotations == 0) {
			total++;
		}
	}

	cout << total << "\n";

	return 0;
}

vector<string> parseFile(const string &filename) {
		ifstream file(filename);

	if (!file.is_open()) {
		cerr << "Error opeing file" << filename << "\n";
	}

	string line;
	vector<string> codes;

	while (getline(file, line)) {
		codes.push_back(line);
	}

	file.close();
	return codes;
}

tuple<string, int> directionDist(const string &code) {
	size_t firstIntIndex = code.find_first_of("0123456789");

	string direction = code.substr(0, firstIntIndex);
	int distance = stoi(code.substr(firstIntIndex));

	return {direction, distance};
}
