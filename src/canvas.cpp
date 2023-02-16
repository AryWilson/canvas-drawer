#include "canvas.h"
#include <cassert>

using namespace std;
using namespace agl;



Canvas::Canvas(int w, int h) : _canvas(w, h)
{
   _canvas = Image(w,h);
   current_col = Pixel{0,0,0};
   current_type = UNDEFINED;
   fill = true;
}

Canvas::~Canvas()
{
}

void Canvas::save(const std::string& filename)
{
   _canvas.save(filename);
}

void Canvas::begin(PrimitiveType type)
{
   //allocate?
   current_type = type;
}

void Canvas::end()
{
   // free?
   //if type = 
   // vertices.empty();
   // vertices.size();
   // vertices.pop_back();
   // vertices.push_back();
   vertices.clear();
}

void Canvas::vertex(int x, int y)
{
   // sepaate for triangle and line?
   // just add to vetex struct, (delete struct when appropriate num of points?)
   vertices.push_back(Point{x,y,current_col});
   if (vertices.size() == 3 && current_type == TRIANGLES){
     
      struct Point c = vertices.back();
      vertices.pop_back();
      struct Point b = vertices.back();
      vertices.pop_back();  
      struct Point a = vertices.back();
      vertices.pop_back(); 
      
      if ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y) == -1){
         struct Point temp = b;
         b = c;
         c = temp;
      }
      if (fill == false){   
         drawline(a,b);
         drawline(b,c);
         drawline(c,a);
      } else {
         triangle(a,b,c);
      }
   } else if (vertices.size() == 2 && current_type == LINES){
      struct Point b = vertices.back();
      vertices.pop_back();
      struct Point a = vertices.back();
      vertices.pop_back();      
      drawline(a,b);
   }

}

void Canvas::color(unsigned char r, unsigned char g, unsigned char b)
{
   current_col = Pixel{r,g,b};

}

void Canvas::background(unsigned char r, unsigned char g, unsigned char b)
{
   struct Pixel col = Pixel{r,g,b};
   for (int i = 0; i< _canvas.height(); i++){
      for (int j = 0; j< _canvas.width(); j++){
         _canvas.set(i,j,col);
      }
   }
}


void Canvas::drawline(struct Point a, struct Point b) {
   struct Pixel p_a = a.col;
   struct Pixel p_b = b.col;
   int W = b.x - a.x;
   int H = b.y - a.y;
   if (abs(H) < abs(W)) {
      if (a.x > b.x){

         struct Pixel temp_p = p_a;
         p_a = p_b;
         p_b = temp_p;

         int tempx = a.x;
         int tempy = a.y;
         a.x = b.x;
         a.y = b.y;
         b.x = tempx;
         b.y = tempy;
      } 
      drawline_low(Point{a.x,a.y,p_a},Point{b.x,b.y,p_b});
   } else {
      if (a.y > b.y) {

         struct Pixel temp_p = p_a;
         p_a = p_b;
         p_b = temp_p;

         int tempx = a.x;
         int tempy = a.y;
         a.x = b.x;
         a.y = b.y;
         b.x = tempx;
         b.y = tempy;
      }
      drawline_high(Point{a.x,a.y,p_a},Point{b.x,b.y,p_b});
   } 
} 

void Canvas::drawline_low(struct Point a, struct Point b) {
   int y = a.y ;
   int W = b.x - a.x ;
   int H = b.y - a.y ;
   int dy= 1 ;
   if (H <0) { // if slope is negative, decrement y
      dy = -1 ;
      H = -H;
   }  
   int F = 2*H - W ;
   for (int x = a.x; x <= b.x; x++) {
      if (x>=0 && y>= 0 && x<_canvas.width() && y<_canvas.height()){
         float per = (b.x-x)/((float)(b.x-a.x));
         unsigned char r = per*(a.col.r) + (1-per)*(b.col.r);
         unsigned char g = per*(a.col.g) + (1-per)*(b.col.g);
         unsigned char bl = per*(a.col.b) + (1-per)*(b.col.b);
         _canvas.set(x,y,Pixel{r,g,bl}) ;
      }
      if (F > 0) {
         y += dy ;
         F += 2*(H-W);
      } else {
         F += 2*H;
      }
   } 
}
void Canvas::drawline_high(struct Point a, struct Point b) {
   int x = a.x ;
   int W = b.x -a.x ;
   int H = b.y -a.y ;
   int dx = 1 ;
   if (W <0) { // if x-slope is negative, decrement x
      dx =-1 ;
      W = -W;
   }  
   int F = 2*W -H ;
   for (int y = a.y; y<= b.y; y++) {
      if (x>=0 && y>= 0 && y<_canvas.width() && x<_canvas.height()){
         float per = (b.y-y)/((float)(b.y-a.y));
         unsigned char r = per*(a.col.r) + (1-per)*(b.col.r);
         unsigned char g = per*(a.col.g) + (1-per)*(b.col.g);
         unsigned char bl = per*(a.col.b) + (1-per)*(b.col.b);
         _canvas.set(x,y,Pixel{r,g,bl}) ;
      }
      if (F > 0) {
         x += dx ;
         F += 2*(W-H);
      } else {
         F += 2*W;
      } 
   }
}
int _max(int a, int b, int c){
   if (a >= b && a >= c){return a;}
   if (b >= a && b >= c){return b;}
   if (c >= b && c >= a){return c;}
   return a;

}

int _min(int a, int b, int c){
   if (a <= b && a <= c){return a;}
   if (b <= a && b <= c){return b;}
   if (c <= b && c <= a){return c;}
   return a;

}
void Canvas::triangle(struct Point a, struct Point b, struct Point c){
   int right = _max(a.x, b.x, c.x);
   int left = _min(a.x, b.x, c.x);
   int up = _max(a.y, b.y, c.y);
   int down = _min(a.y, b.y, c.y);

   float fa = (b.y - a.y)*(c.x - a.x) - (b.x - a.x)*(c.y - a.y);
   float fb = (c.y - a.y)*(b.x - a.x) - (c.x - a.x)*(b.y - a.y);
   // f(x,y) = (a.y - b.y)*x + (b.x - a.x)*y + (a.x)*(b.y) - (b.x)*(a.y) = 0
   for(int i = left; i<=right; i++){
      for(int j = down; j<=up; j++){
         // ((b.y - a.y)*(i - a.x) - (b.x - a.x)*(j - a.y))/fa;
         float alpha = ((b.y - a.y)*(i - a.x) - (b.x - a.x)*(j - a.y))/fa;
         float beta = ((c.y - a.y)*(i - a.x) - (c.x - a.x)*(j - a.y))/fb;
         float gamma = 1.0f - alpha - beta;
         if(alpha >= 0 && beta >= 0 && gamma >= 0){
            unsigned char r = (alpha)*(a.col.r) + (beta)*(b.col.r) + (gamma)*(c.col.r);
            unsigned char g = (alpha)*(a.col.g) + (beta)*(b.col.g) + (gamma)*(c.col.g);
            unsigned char bl = (alpha)*(a.col.b) + (beta)*(b.col.b) + (gamma)*(c.col.b);
            _canvas.set(i,j,Pixel{r,g,bl});
         }
      }

   }

}




