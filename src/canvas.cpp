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
   // just add to vetex struct, (delete struct when appropriate num of points?)
   vertices.push_back(Point{x,y,current_col});
   if (vertices.size() == 1 && current_type == POINTS){
      struct Point a = vertices.back();
      vertices.pop_back();
      _canvas.set(a.x,a.y,a.col);
   }
   if (vertices.size() == 3 && current_type == TRIANGLES){
     
      struct Point c = vertices.back();
      vertices.pop_back();
      struct Point b = vertices.back();
      vertices.pop_back();  
      struct Point a = vertices.back();
      vertices.pop_back(); 
      
      if ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y) == -1){
         // std::cout << "swap" << std::endl;
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
   for (int i = 0; i< _canvas.width(); i++){
      for (int j = 0; j< _canvas.height(); j++){
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
      if (x>=0 && y>= 0 && x<=_canvas.width() && y<=_canvas.height()){
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
      if (x>=0 && y>= 0 && x<=_canvas.width() && y<=_canvas.height()){
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
int Canvas::implicit(int x, int y, struct Point a, struct Point b){
   return (b.x-a.x)*(y-a.y) - (b.y-a.y)*(x-a.x);
}
void Canvas::triangle(struct Point a, struct Point b, struct Point c){
   int right = max(a.x, max(b.x, c.x)) + 1;
   int left = min(a.x, min(b.x, c.x)) - 1;
   int up = max(a.y, max(b.y, c.y)) + 1;
   int down = min(a.y, min(b.y, c.y)) - 1;

   float fa = implicit(a.x, a.y, b,c);
   float fb = implicit(b.x, b.y, c,a);;
   float fc = implicit(c.x, c.y, a,b);;
   // f(x,y) = (a.y - b.y)*x + (b.x - a.x)*y + (a.x)*(b.y) - (b.x)*(a.y) = 0
   for(int j = down; j<=up; j++){
      for(int i = left; i<=right; i++){
         // ((b.y - a.y)*(i - a.x) - (b.x - a.x)*(j - a.y))/fa;
         float alpha = implicit(i,j,b,c)/fa;
         float beta = implicit(i,j,c,a)/fb;
         float gamma = implicit(i,j,a,b)/fc;
         if(alpha >= 0 && beta >= 0 && gamma >= 0){
            unsigned char r = (alpha)*(a.col.r) + (beta)*(b.col.r) + (gamma)*(c.col.r);
            unsigned char g = (alpha)*(a.col.g) + (beta)*(b.col.g) + (gamma)*(c.col.g);
            unsigned char bl = (alpha)*(a.col.b) + (beta)*(b.col.b) + (gamma)*(c.col.b);
            _canvas.set(i,j,Pixel{r,g,bl});
         }
      }

   }

}


void Canvas::star(int cx, int cy, int size){
   float delta = (4*acos(0.0f))/5.0f;
   float start =  rand() % 4*acos(0.0f);
   for(int i = 0; i<=5;i++){
      
      struct Point a = Point{cx + (int) floor(size*(cos(start + i*delta))), cy + (int) floor(size*(sin(start + i*delta))),current_col};   
      struct Point b = Point{cx + (int) floor(size*(cos(start + (i+1)*delta))), cy + (int) floor(size*(sin(start + (i+1)*delta))),current_col};   

      triangle(a,b,Point{cx,cy,current_col});
      struct Point c = Point{cx + (int) floor(2*size*(cos(start + i*delta + delta/2.0f))), cy + (int) floor(2*size*(sin(start + i*delta + delta/2.0f))),current_col};  
      triangle(a,b,c);
   }
}
void Canvas::circle(int cx, int cy, int r){
   // rose(cx-r,cy,2*r,1,1);
   ngon(cx,cy,r,r);
}
void Canvas::rose(int cx, int cy, int r, int n, int d){
   if (n <= 0 || d <= 0){return;}
   float m = max(n,d);
   float delta = 1/((m)*(4)*acos(0.0f));
   float k = n/((float) d);
   for(float theta = 0; theta <= (m)*(4)*acos(0.0f); theta += delta){
      struct Point a = Point{cx+(int) floor(r*cos(k*theta)*cos(theta)),cy+(int) floor(r*cos(k*theta)*sin(theta)),current_col};
      struct Point b = Point{cx+(int) floor(r*cos(k*(theta + delta))*cos(theta + delta)),cy+(int) floor(r*cos(k*(theta + delta))*sin(theta + delta)),current_col};
      drawline(a,b);
   }
}

void Canvas::roseLine(int cx, int cy, int r, int n, int d){
   float m = max(n,d);
   float delta = 1/((m)*(4)*acos(0.0f));
   float k = n/((float) d);
   float endpt = ((4)*acos(0.0f))/n;
   for(float theta = 0; theta <= (m)*(4)*acos(0.0f); theta += delta){
      struct Point a = Point{cx+(int) floor(r*cos(k*theta)*cos(theta)),cy+(int) floor(r*cos(k*theta)*sin(theta)),current_col};
      struct Point b = Point{cx+(int) floor(r*cos(k*(theta + endpt))*cos(theta + endpt)),cy+(int) floor(r*cos(k*(theta + endpt))*sin(theta + endpt)),current_col};
      drawline(a,b);
   }
}

void Canvas::ngon(int cx, int cy, int r, int sides){
   if (sides<=0){
      return;
   }
   float delta = ((2)*acos(0.0f))/sides;
   int _cx = cx - r;
   int _r = 2*r;
   for(float theta = 0; theta <= (2)*acos(0.0f); theta += delta){
      struct Point a = Point{_cx+(int) floor(_r*cos(theta)*cos(theta)),cy+(int) floor(_r*cos(theta)*sin(theta)),current_col};
      struct Point b = Point{_cx+(int) floor(_r*cos((theta + delta))*cos(theta + delta)),cy+(int) floor(_r*cos((theta + delta))*sin(theta + delta)),current_col};
      if(fill){
         triangle(Point{cx,cy,current_col},a,b);
      }else{
         drawline(a,b);
      }
   }
}

void Canvas::setFill(bool f){fill = f;}



