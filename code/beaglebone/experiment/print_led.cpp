#include <iostream>
#include <fstream>

using namespace std;

const char *LEDPath = "/sys/class/leds/beaglebone:green:usr0/brightness";

int main() {
	ifstream *fStream = new ifstream();
  fStream->open(LEDPath);

  char *buffer = new char[100];
  bool on = false;

  if (!fStream->is_open()) {
    cerr << "Failed to open file: " << LEDPath << endl;
  }

  while (fStream->is_open()) {
    if (fStream->eof()) {
      fStream->close();
      fStream->open(LEDPath);
    } else {
      *fStream >> buffer;
      bool new_on = (buffer[0] > '0');

      if (on != new_on)
        cout << new_on ? '1' : '0';

      on = new_on;
    }
  }

  if (buffer) delete [] buffer;

  if (fStream) {
    fStream->close();
    delete fStream;
  }

	return 0;
}
