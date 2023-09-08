#include <array>
using namespace std;

class Display {
public:
  /**
   * Renders the monochrome display on an HTML canvas given a display matrix. Here `true`
   * indicates that the primary color is set and `false` indicates the secondary color.
  */
  void drawDisplay(array<array<bool, 64>, 32> &display);

  void shutDown();
};