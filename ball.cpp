//g++ -std=c++11
#include <iostream>


//constantes
const double G = 9.81;
const double DT = 0.001;
const int N = 10000;
const double  K = 199.87; 


struct particle {

  double x{0} , y{0}, vx{0}, vy{0} , fx{0}, fy{0};
  double mass{0}, rad{0};
};

void compute_forces(particle & bola);
void time_step(particle & bola, const double dt);

int main(void)
{
  particle ball;
  
  //initial conditions
  ball.y = 9.88;
  ball.mass = 2.65;
  ball.rad = 0.15;
  
  std::cout << ball.x << "    " << ball.y << std::endl;
  
  
  for  (int ii = 0; ii <= N ; ++ii ){
      compute_forces(ball);
      time_step(ball,DT);
      
      std::cout << ii*DT << "    "
		<< ball.x << "    " << ball.y << "    "
		<< ball.vx << "    " << ball.vy
		<< std::endl;
    }
  
  return 0;
}


void compute_forces(particle & bola)
{
  bola.fx=0.0;
  bola.fy=0.0;
  
  bola.fy += -bola.mass*G;

  double delta = bola.rad - bola.y;
  if(delta > 0)

    bola.fy += K*delta;
    
}

void time_step(particle & bola, const double dt)
{
  bola.x= bola.x +dt*bola.vx + 0.5*dt*dt*bola.fx/bola.mass;
  bola.y= bola.y +dt*bola.vy + 0.5*dt*dt*bola.fy/bola.mass;

  bola.vx= bola.vx + dt*bola.fx/bola.mass;
  bola.vy= bola.vy + dt*bola.fy/bola.mass;

}
