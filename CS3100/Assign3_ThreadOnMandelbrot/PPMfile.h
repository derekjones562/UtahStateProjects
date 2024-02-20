#include<cmath>
#include<vector>
#include<sstream>

//
//params are x,y coordinates. returns the color 1-15. returns 0 if black
int generateMbSetat(double x0, double y0, int mx)
{
	//For each pixel on the screen do:
	 // x0 = std::fmod (x0, -2.5)+1.0;//scaled x coordinate of pixel (must be scaled to lie somewhere in the mandelbrot X scale (-2.5, 1)
	  //y0 = std::fmod (y0, -1.0)+1.0;//scaled y coordinate of pixel (must be scaled to lie somewhere in the mandelbrot Y scale (-1, 1)

	  double x = 0.0;
	  double y = 0.0;

	  int iteration = 0;
	  int max_iteration = 1000;

	  while( x*x + y*y < 2*2  && iteration < max_iteration )
	  {
		double xtemp = x*x - y*y + x0;
		y = 2*x*y + y0;

		x = xtemp;

		iteration += 1;
	  }
	  int color =iteration % mx;
	  if(iteration==max_iteration)
			color = 0;//black
	  return color;
	 // plot(x0,y0,color);
//Psuedocode from wikipedia 
}

std::string generatePartofMbrotSet(double maxX, double maxY, double minX, double minY, int pixelx, int pixely, const int maxV) //PixelsPerLine
{
	//std::vector<std::vector<int>> mbrotset;
	//std::vector<int> lineofPixels(PPL);
	
	std::stringstream ss;
	auto y = minY;
	for(int i =0; i< pixely; i++)
	{
		//lineofPixels.erase(lineofPixels.begin(), lineofPixels.end());//empty line of pixels for the next go around
		auto x=minX;
		for(int j=0; j<pixelx; j++)
		{
			int temp = generateMbSetat(x, y, maxV);
			ss<<temp<<" ";
			//lineofPixels.push_back(temp);
			x+=(maxX - minX)/pixelx;
		}
		//mbrotset.push_back(lineofPixels);
		ss<<"\n";
		y+=(maxY-minY)/pixely;
	}
	return ss.str();
}