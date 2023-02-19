/*-----------------------------------------------
 * Author:
 * Date:
 * Description:
 ----------------------------------------------*/

#ifndef canvas_H_
#define canvas_H_

#include <string>
#include <vector>
#include "image.h"
#include <math.h>

namespace agl
{

   /**
    * @brief Holder for a point
    * 
    */
   struct Point {
      int x;
      int y;
      struct Pixel col;
   };

   enum PrimitiveType {UNDEFINED, POINTS, LINES, TRIANGLES};
   class Canvas
   {
   public:
      Canvas(int w, int h);
      virtual ~Canvas();

      // Save to file
      void save(const std::string& filename);

      // Draw primitives with a given type (either LINES or TRIANGLES)
      // For example, the following draws a red line followed by a green line
      // begin(LINES);
      //    color(255,0,0);
      //    vertex(0,0);
      //    vertex(100,0);
      //    color(0,255,0);
      //    vertex(0, 0);
      //    vertex(0,100);
      // end();
      void begin(PrimitiveType type);
      void end();

      // Specifiy a vertex at raster position (x,y)
      // x corresponds to the column; y to the row
      void vertex(int x, int y);

      // Specify a color. Color components are in range [0,255]
      void color(unsigned char r, unsigned char g, unsigned char b);

      // Fill the canvas with the given background color
      void background(unsigned char r, unsigned char g, unsigned char b);
      // draws line from indicated point a to point b
      void drawline(struct Point a, struct Point b);
      //internal function for drawing lines with slops within [-pi/4,pi/4]
      void drawline_low (struct Point a, struct Point b);
      //internal function for drawing lines with slops within [-pi/2,-pi/4] or [pi/4,pi/2]
      void drawline_high (struct Point a, struct Point b);
      // draws triangles from 3 given points, supports interpilation and fill boolean 
      void triangle(struct Point a, struct Point b, struct Point c);
      // draws a solid color star at indicated x,y coords with given size, which is taken as the length of an edge in pixels. The angle of the star is random.
      void star(int cx, int cy, int size);  
      // draws a circle useing the parameters x,y as the center coords and the radius r, supports fill, does not support iterpolation
      void circle(int cx, int cy, int r);
      // draws a mathematical rose using the paramters x,y as the center, r as the radius, n as the numerator of k, and d as the denominator of k. Does not support fill or interpolation
      void rose(int cx, int cy, int r, int n, int d);

      //works intermitantly, when d=1, don't use
      void roseLine(int cx, int cy, int r, int n, int d);
      // draws a polygon at the indicated x,y coordinates with the indicated radius,r, with the indicated number of sides
      void ngon(int cx, int cy, int r, int sides);
      //toggle internal fill boolean, works on ngons, triangles, and circles. Roses and lines are always 'unfilled', stars are always filled.
      void setFill(bool f);


   private:
      Image _canvas;
      struct Pixel current_col;
      PrimitiveType current_type;
      std::vector<struct Point> vertices;
      bool fill;
   };
}

#endif


