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
private:
  /**
   * Forwards TypeScript function to render a single pixel. Its description is:
   * Draws a single pixel at coordinates (x,y) in the HTML canvas. The color corresponds to either
   * the primary color (for `true`) or the secondary color (for `false`)
  */
  void renderPixel(int x, int y, bool color);
};