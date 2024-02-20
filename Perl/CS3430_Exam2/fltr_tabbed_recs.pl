#!/usr/bin/perl
use strict;
use warnings;
my $date;
my $ip;
my $time;
my $method;
my $trnsbts;
my $resultsstatus;
while(<>)
{
	my@line = split(/ /,$_);
	
	for my$thing (@line)
	{
		#print "$thing\n";
		if($thing=~/(\d{2}).(\d{3}).(\d{2}).(\d{2})/)
			{$ip = $thing;
				#print "$ip\n";
			}
		
		if($thing=~/\[(\d{2})\/(\w{3})\/(\d{4}):(\d{2}):(\d{2}):(\d{2})/)
		{
			$time="";
			my@datetime = split(/:/, $thing);
			for my $item (@datetime)
			{
				if($item=~/\[(\d{2})\/(\w{3})\/(\d{4})/)
				{my@d=split(/\[/, $item);
					$date= $d[1];}
				else
				{
					$time="".$time.$item;
					if($time!~/(\d{2}):(\d{2}):(\d{2})/)
						{$time="".$time."\:";
							
						}
					#print "$time\n";
				}
				#print "$item\n";
			}
			#print "$time\n";
		}
		if($thing=~/"GET/)
		{
			$method ="GET";
			#print "$method\n";
		}
		if($thing=~/(\d{4,6})/)
		{
			$trnsbts=$thing;
			#print "$trnsbts\n";
		}
		if($thing =~/\b\d{3}\b/)
		{
			$resultsstatus=$thing;
			#print "$resultsstatus\n";
			
		}
		
	}
	print "$date\t$time\t$method\t$ip\t$trnsbts\t$resultsstatus\n";
	
}