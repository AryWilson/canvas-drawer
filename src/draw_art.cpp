#include <iostream>
#include "canvas.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
   Canvas drawer(640, 380);
   drawer.background(0,0,0);
   drawer.color(100,20,200);
   drawer.ngon(300,200,100,-3);
   drawer.save("something.png");
   return 0;
   drawer.begin(TRIANGLES);

   ///
   drawer.color(20, 0, 20);
   drawer.vertex(640, 380);

   drawer.color(0, 0, 30);
   drawer.vertex(0, 380);
   
   drawer.color(0,0,0);
   drawer.vertex(640, 0);
   drawer.end();

   drawer.begin(TRIANGLES);
   drawer.color(0, 0, 0);
   drawer.vertex(0, 380);

   drawer.color(20, 0, 20);
   drawer.vertex(640, 0);

   drawer.color(0, 0, 30);
   drawer.vertex(0, 0);
   drawer.end();


   srand(time(0));
   drawer.begin(POINTS);
   for(int i = 0; i<6; i++){
      int x = rand()%640;
      int y = rand()%380;
      unsigned char r = rand()%45;
      unsigned char g = rand()%45;
      unsigned char b = rand()%45;
      int d = 3 + (rand() % 11);
      int n = 3 + (rand() % 11);
      drawer.color(r,g,b);
      drawer.rose(x,y, 8 + (rand()%12),n,d);

      drawer.color(2*r,2*g,2*b);
      drawer.rose(x,y, 2 + (rand()%5),n,d);
      
      drawer.color(220,220,220);
      drawer.vertex(x,y);

      drawer.color(90,90,30);
      drawer.star(rand()%640,rand()%380,rand()%4);
   }
   for(int i=0;i<250;i++){
      drawer.color(rand()%150,rand()%150,rand()%150);
      drawer.vertex(rand()%640, rand()%380);
   }
   drawer.end();
   drawer.save("stars.png");
   
   drawer.background(210,140,00);
   drawer.setFill(true);
   int size = 22;
   int in = 18;
   bool toggle = 0;
   for(int j = 0; j<380; j+=size){
      toggle = !toggle;
      for(int i = (toggle)*(2*size); i<640; i+=4*size){
         drawer.setFill(true);
         drawer.color(240,220,20);
         drawer.ngon(i,j,size,6);
      
         drawer.setFill(false);
         drawer.color(210,140,00);
         drawer.ngon(i,j,in,6);
         drawer.ngon(i,j,in-1,6);
      }
   }
   drawer.save("honey.png");
   return 0;
}

