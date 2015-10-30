#include<sys/wait.h>
#include<unistd.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<ctime>
#include<chrono>

void printmenu()
{
	std::cout<<"\n[cmd]:";
}
int main()
{

	std::chrono::time_point<std::chrono::system_clock> start, end;
	while(true)
	{
		/*getinput
		parse input
		switch
			histor
			ptime
			execcute history
			default
				fork and exec*/
		std::string line;
		printmenu();
		std::getline(std::cin, line);
		std::vector<char*> args;
		std::vector<char*> history;
		args.push_back(strdup(line.c_str()));
		args.push_back(nullptr);
		history.push_back(args[0]);
		if(args[0]=="exit")
			break;

		start= std::chrono::system_clock::now();
		
		auto pid = fork();
		if(pid<0)
		{
			std::cerr<<"couldn't fork"<<std::endl;
		}
		if(pid==0)
		{
			if( args[0]=="^")
			{
				execvp(history[(int)args[1]]);
			}
			else
			{
				execvp(args[0], args.data());
			}
		}
		else
		{
			wait(pid, nullptr, 0);
		}
		if(args[0] =="history" )
		{
			for(int i =0; i != history.size(); i++)
			{
				std::cout<< i<<" "<< history[i]<<std::endl;
			}
		}
		
		if(args[0] == "ptime")
		{
			end= std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end-start;
			std::cout << "Time spent executing child processes:"<<(int)elapsed_seconds.count()<<" Seconds "
				<< (int)(elapsed_seconds.count()*1000) << " milliseconds " 
				<< (int)(elapsed_seconds.count()*1000000)%1000 <<" microseconds "<< std::endl;
		}
	}
	return 0;
}