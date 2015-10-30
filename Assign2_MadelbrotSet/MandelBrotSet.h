#include<iostream>
//https://www.youtube.com/watch?v=WXdB_cLe8ZI
void iterate(double &x, double &y, double &a, double &b)
{
	double tempx=x*x-y*y+a;
	y=2*x*y+b;
	x=tempx;
}
void iterateManyTimes(int n, double &x, double &y, double &a, double &b)
{
	for(int i=0; i<n; i++)
	{
		iterate(x,y,a,b);
	}
}
bool seriesDiverg(int n, double &x, double &y, double &a, double &b)
{
	for(int i=0; i<n; i++)
	{
		iterate(x, y, a, b);
		if(x*x+y*y>4.0)
			return true;
	}
	return false;
}
void drawAB(double a, double b)
{
	std::cout<<"[";
}
void drawXY(double x, double y)
{
	std::cout<<",";
	//(200+x*100; 200-y*100);
}

void draw(double &a, double &b, double &x, double &y)
{
	bool stilldrawing = true;
	while(stilldrawing)
	{
		for(int i =0; i <100; i++)
		{
			a=a+0.1;
			if(a>=2)
			{
				a=-2;
				b+=0.1;
			}
			if(b>=2)
			{
				stilldrawing=false;
			}
			if(seriesDiverg(100,x,y,a,b))
			{
				//drawAB(a,b);
				std::cout<<".";
			}
			else
			{std::cout<<" ";
			}
		}
		std::cout<<"\n";
	}
}
void iterateAndDraw(int n, double &x, double &y, double &a, double &b)
{
	for(int i = 0; i<n; i++)
	{
		iterate(x,y,a,b);
		drawXY(x, y);
	}
}


void print(double xpos, double ypos)
{
	std::cout<<"("<<xpos<<", "<<ypos<<")\n";
}
void generateMandelbrotSet()
{
	double x =0,y=0,a=-2,b=-2;
	draw(a,b,x,y);
	//print(x, y);
}


