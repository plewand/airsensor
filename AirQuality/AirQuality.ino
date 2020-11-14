#include "Debug.h"
#include "Environment.h"

static Environment environment;

void setup() {  
  
  environment.initialize();
}


void loop() {
  
  environment.loopIteration();
}
