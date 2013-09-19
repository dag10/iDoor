#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

const char *led_path_format = "/sys/class/leds/beaglebone:green:usr%d/brightness";
const int MAX_LEDS = 4;
const int SPEED = 10;

int main() {
  ofstream *file_stream = new ofstream();

  bool on = false;
  int led_id = 0;
  char *led_path = new char[100];

  while (true) {
    led_id = (led_id + 1) % MAX_LEDS;
    if (led_id == 0) on = !on;

    sprintf(led_path, led_path_format, led_id);
    file_stream->open(led_path);

    if (!file_stream->is_open()) {
      cerr << "Failed to open file: " << led_path << endl;
      break;
    }

    file_stream->put(on ? '1' : '0');
    cout << led_id << " is " << (on ? "ON" : "OFF") << endl;
    file_stream->flush();
    file_stream->close();

    usleep(1000000 / SPEED);
  }

  if (led_path) {
    delete [] led_path;
  }

  if (file_stream) {
    file_stream->close();
    delete file_stream;
  }

  return 0;
}
