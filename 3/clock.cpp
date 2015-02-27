#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "clock.h"
#include "gamedata.h"
#include "ioManager.h"

Clock& Clock::getInstance() {
  if ( SDL_WasInit(SDL_INIT_VIDEO) == 0) {
    throw std::string("Must init SDL before Clock");
  }
  static Clock clock; 
  return clock;
}

Clock::Clock() :
  ticks(0),
  frames(0),
  started(false), 
  paused(false), 
  sloMo(false), 
  sumOfTicks(1)
  {
  start();
}

Clock::Clock(const Clock& c) :
  ticks(c.ticks), 
  frames(c.frames),
  started(c.started), 
  paused(c.paused), 
  sloMo(c.sloMo), 
  sumOfTicks(c.sumOfTicks)
  {
  start();
}

void Clock::draw() const { 
  IOManager::getInstance().printMessageValueAt("ticks: ", ticks, 10, 30);
}

void Clock::update() { 
  //ticks = 5;
  if(!paused){ 
    if(sloMo){
   	 ++frames;
	 ticks = 2;
    } else {
   	 frames+=9;
	 ticks = 6;
    } 
  }else{
	ticks  = 0 ;
	frames = 0;
  }
  
  sumOfTicks += ticks;
  if(sumOfTicks > 1000){
	sumOfTicks = 1;
	frames = 0;
  }
  std::cout<<"frames = " << frames << std::endl;
}

unsigned int Clock::getTicksSinceLastFrame() const {
  return ticks;
}

void Clock::toggleSloMo() {
	if(sloMo) 
		sloMo = false;
	else
		sloMo = true;
}

int Clock::getFps() const { 
  std::cout<<"frames = " << frames << std::endl;
  std::cout<<"sumOfTicks = " << sumOfTicks << std::endl;
  int fps = ((frames*1000)/(9*sumOfTicks));
  std::cout<<"fps = " << fps << std::endl;
  return fps;
}

void Clock::start() { 
  started = true; 
  paused = false; 
}

void Clock::pause() { 
  paused = true;
 // started = false;
  //std::cout << "pause: Not implemented yet" << std::endl;
}

void Clock::unpause() { 
//  started = true;
   paused = false;
  //std::cout << "unpause: Not implemented yet" << std::endl;
}

