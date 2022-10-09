#include <iostream>
#include <cmath>
#include <unistd.h>
#include <iomanip>
#include <SDL2/SDL.h>

#include "Object.h"

#define G 6.67 * pow( 10,-11)
#define PI 3.14159265358979323
#define WINDOW_WIDTH 700

void setLength(vector& v, double length);
double getLength(vector v);

void setAngle(vector& v, double a){
	double length = getLength(v);

	v.direction = cos(a) * length;
	v.magnitude = sin(a) * length;

}

double getAngle(vector v){
	return atan2(v.magnitude , v.direction); 
}

void setLength(vector& v, double length){
	double angle = getAngle(v);

	v.direction = cos(angle) * length;
	v.magnitude = sin(angle) * length;
}

double getLength(vector v){
	return sqrt(v.direction * v.direction + v.magnitude * v.magnitude);
}

double angle(Object o, Object o1){
	return atan2(o1.y - o.y, o1.x - o.x);
}

double distance(Object o, Object o1){
	double dx = o1.x - o.x;
	double dy = o1.y - o.y;
	
	return sqrt(dx*dx + dy*dy);
}

double gravitation(double m1, double m2, double r){
	return (G*m1*m2) / (r*r);
}

void gravitate(Object& o, Object o1)
{
	vector g;
	double d = distance(o,o1);
	double a = angle(o, o1);

	double gr  = gravitation(o.m, o1.m, d);
	setLength(g, gr);	
	setAngle(g, a);

	o.v = o.v + g;
}

void print(Object o, Object o1, double r)
{
	std::cout << "\nEarth coordinates: " << '(' << o.x << ',' << o.y << ')' << " | " << "Mars coordinates: " << '(' << o1.x << ',' << o1.y << ')';
}

int main()
{
	int ret;
	SDL_Event event;
   	SDL_Renderer *renderer;
    	SDL_Window *window;

    	SDL_Init(SDL_INIT_VIDEO);
    	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    	SDL_RenderClear(renderer);
    	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	for (int i = 0; i < WINDOW_WIDTH; ++i)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
       		SDL_RenderDrawPoint(renderer, i, WINDOW_WIDTH/2);
	}
	for (int i = 0; i < WINDOW_WIDTH; ++i)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
       		SDL_RenderDrawPoint(renderer, WINDOW_WIDTH/2, i);
	}

  // 5.972 × 10²⁴
  //

  	Object Earth (50,200 ,10, 10, -PI*2);
  	Object Sun (0,0, 90000000000000, 0, 0);
	Object Mars (-30,-200, 5, 12, 3);
	

	while(1)
	{
		while (SDL_PollEvent(&event)) 
		{
			if(event.type == SDL_QUIT)
				goto ret;
       			
    		}	
	 	double r = Sun.x - Earth.x / Sun.y - Earth.y;
		
	 	gravitate(Earth, Sun);
		gravitate(Mars, Sun);

		gravitate(Earth, Mars);
		gravitate(Mars, Earth);

	 	gravitate(Sun, Earth);
		gravitate(Sun, Mars);

	 	Earth.x += Earth.v.direction;
		Earth.y += Earth.v.magnitude;
	 	
		Mars.x += Mars.v.direction;
		Mars.y += Mars.v.magnitude;
	
 	

	 	print(Earth, Mars, r);	 

	 	for (int i = 0; i < WINDOW_WIDTH; ++i)
	 	{
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
       	 		SDL_RenderDrawPoint(renderer, Earth.x+WINDOW_WIDTH/2, -Earth.y+WINDOW_WIDTH/2);
	 	}

	 	for (int i = 0; i < WINDOW_WIDTH; ++i)
	 	{
	 		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	 		SDL_RenderDrawPoint(renderer, Sun.x+WINDOW_WIDTH/2, -Sun.y+WINDOW_WIDTH/2);
	 	}

		for (int i = 0; i < WINDOW_WIDTH; ++i)
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderDrawPoint(renderer, Mars.x+WINDOW_WIDTH/2, -Mars.y+WINDOW_WIDTH/2);
		}
		SDL_RenderPresent(renderer); 
   	 
		SDL_Delay(250);
		sleep(0.25);
 		
	 
	}

	ret:;

    	SDL_DestroyRenderer(renderer);
    	SDL_DestroyWindow(window);
    	SDL_Quit();
    
}
