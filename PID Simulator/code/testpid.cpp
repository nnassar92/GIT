#include "pid.hpp"
#include "output.hpp"
#include "model.hpp"

using namespace std;

int main()
{	
	
	pid PID(2,0.01);
	
	float y;float *x;float *u;
	y=output(PID.getx());
	PID.updatey(y);
	u=PID.control();
	x=model(PID.getx(),u[0]);

	cout<<'x'<<x[0]<<','<<x[1]<<'y'<<y<<endl;
	
	return 0;
}
