#include <iostream>
#include "canvas.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
   Canvas drawer(640, 380);
   drawer.background(0,0,0);
   drawer.color(255,0,255);
   drawer.setFill(false);
   drawer.circle(300,200,10);
   drawer.save("circle1.png");
   drawer.background(0,0,0);
   drawer.color(255,0,255);
   drawer.circle(300,200,50);
   drawer.save("circle2.png");
   drawer.background(0,0,0);
   drawer.color(255,0,255);
   drawer.circle(300,200,100);
   drawer.save("circle3.png");
   drawer.background(0,0,0);
   drawer.color(255,0,255);
   drawer.ngon(300,200,30,5);
   drawer.save("pentagon.png");
   drawer.background(0,0,0);
   drawer.color(255,0,255);
   drawer.ngon(300,200,30,6);
   drawer.save("hexagon.png");
   drawer.background(0,0,0);
   drawer.color(255,0,255);
   drawer.ngon(300,200,30,3);
   drawer.save("triangle.png");
   drawer.background(0,0,0);
   drawer.color(255,0,255);
   drawer.ngon(300,200,30,4);
   drawer.save("square.png");

   drawer.background(0,0,0);
   drawer.color(255,255,0);
   drawer.star(50,50,10);
   drawer.color(255,255,255);
   drawer.star(5,300,5);
   drawer.color(100,100,0);
   drawer.star(500,100,15);
   drawer.save("star.png");


   drawer.background(0,0,0);
   drawer.color(255,0,255);
   drawer.circle(300,200,30);
   drawer.save("circle.png");

   drawer.background(0,0,0);
   drawer.color(255,0,255);
   drawer.rose(300,200,30,1,3);
   drawer.save("rose10.png");

   drawer.background(0,0,0);
   drawer.color(255,0,255);
   drawer.rose(300,200,30,5,1);
   drawer.save("rose9.png");

   drawer.background(0,0,0);
   drawer.color(255,0,255);
   drawer.rose(300,200,30,3,5);
   drawer.save("rose11.png");


}

