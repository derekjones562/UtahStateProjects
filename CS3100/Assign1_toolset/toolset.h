#include<ctime>
#include<cmath>
#include<vector>
#include<numeric>
#include<algorithm>
#include<functional>

//A function that computes the average (mean) of elements in any container
template <typename Etype>
Etype averageOfContainer(std::vector<Etype> container)
{
	Etype sum=0;
	return (std::accumulate( container.begin(), container.end(), sum))/container.size();
}

//A function that computes the standard deviation of elements in any container
template <typename Etype>
double standardDiviation(std::vector<Etype> container)
{
	//Find the mean.
	Etype mean = averageOfContainer(container);
	//Find the variance. The variance is the average of the squared differences from the mean. 
	//To get the variance, first calculate the difference from the mean for each sample number. 
	//Square each number then average the results.
	std::vector<Etype> minusMeanVec(container.size());
	std::vector<Etype> differenceSquared(container.size());

	std::transform(container.begin(),container.end(), minusMeanVec.begin(), [mean](Etype i) { return (i - mean); });
	int e =2; //exponent
	std::transform(minusMeanVec.begin(), minusMeanVec.end(), differenceSquared.begin(),[e](Etype i) { return pow(i, e);} );
	double varia = averageOfContainer(differenceSquared);

	//The standard deviation is the square root of the variance.
	return sqrt(varia);
}

//A function that times the processing of another function
template <typename Etype>
double timingOfFunction(Etype const & f)
{
	std::clock_t    start, end;
	start = std::clock();
	f;
	end = std::clock();
	return difftime(end, start);
}

//A function that repeatedly invokes another function, 
//and returns the average and standard deviation of the time taken.
template <typename Etype>
double averageTime(Etype const & f)
{
	std::vector<double> times;
	std::generate(times.begin(), times.end(), [&](){return timingOfFunction(f);});
	return averageOfContainer(times);
}



