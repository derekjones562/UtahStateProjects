#!/usr/bin/perl

use strict;
use warnings;
use List::Util qw(sum); ## import the sum sub from List::Util package

my $short_temp_log = '
2015-04-08_16-53-14 22.25
2015-04-11_16-56-58 22.312
2015-04-11_17-06-58 22.312
2015-04-11_17-16-58 23.125
2015-04-11_17-26-58 23.0
';

my $long_temp_log = '
2015-04-08_16-53-14 22.25
2015-04-11_16-56-58 22.312
2015-04-11_17-06-58 22.312
2015-04-11_17-16-58 23.125
2015-04-11_17-26-58 23.0
2015-04-11_17-36-58 23.062
2015-04-11_17-46-58 23.062
2015-04-11_17-56-58 23.125
2015-04-11_18-06-58 23.25
2015-04-11_18-16-58 23.312
2015-04-11_18-26-58 23.312
2015-04-11_18-36-58 23.312
2015-04-11_18-46-58 23.187
2015-04-11_18-56-58 23.0
2015-04-11_19-06-58 22.75
2015-04-11_19-16-58 22.687
2015-04-11_19-26-58 22.625
2015-04-11_19-36-58 22.562
2015-04-11_19-46-58 22.312
2015-04-11_19-56-58 22.187
2015-04-11_20-06-58 22.0
2015-04-11_20-16-58 21.75
2015-04-11_20-26-58 21.687
2015-04-11_20-36-58 21.125
2015-04-11_20-46-58 20.687
2015-04-11_20-56-58 20.5
2015-04-11_21-06-58 20.375
2015-04-11_21-16-58 20.187
2015-04-11_21-26-58 20.062
2015-04-11_21-36-58 20.062
2015-04-11_21-46-58 20.0
2015-04-11_21-56-58 19.812
';

sub process_temp_log_record {
   my $rawlogEntry = shift();
   my @processedLog;
   my $numString="";
   
   foreach my $s (split(//,$rawlogEntry))
   {
   		if($s =~ '-'||$s=~'_'||$s=~" "||$s=~'\n')
   		{
   			my $numInt = int($numString);
   			push(@processedLog, $numInt);
   			$numString="";
   		}
   		else
   		{
   			$numString .= $s;
   		}
   }
   my $numInt = $numString;
   push(@processedLog, $numInt);
   return \@processedLog;
}

sub process_temp_log {
    my $logEntry = shift();
    my @processedLog;
    my $singleLog="";
    
    my @splitLog = split(//, $logEntry);
    
    foreach my $s (0..$#splitLog)
    {    	
    	if($splitLog[$s]=~"\n")
    	{
    		if($s!=0)
    		{
    			my @temp =process_temp_log_record($singleLog);
    			push(@processedLog,@temp);
    		}
    		$singleLog="";
    	}
    	else
    	{
    		$singleLog.=$splitLog[$s];
    	}
    }
    return @processedLog;
}

sub display_max_celsius_temp {
    my $tempLog =shift();
    my @processedTempLog = process_temp_log($tempLog);
	my$maxTempIndex =0;
	my$currMaxTemp=$processedTempLog[0][6];
	
	foreach my $t (1..$#processedTempLog)
	{
		if($processedTempLog[$t][6]>$currMaxTemp)
		{
			$currMaxTemp = $processedTempLog[$t][6];
			$maxTempIndex = $t;
		}
		
	}
	print "Maximum Celcius Temperature of $processedTempLog[$maxTempIndex][6]";
	print " was at $processedTempLog[$maxTempIndex][3]:$processedTempLog[$maxTempIndex][4]:$processedTempLog[$maxTempIndex][5]";
	print " on $processedTempLog[$maxTempIndex][1]\\$processedTempLog[$maxTempIndex][2]\\$processedTempLog[$maxTempIndex][0]\n";
}

sub display_min_celsius_temp {
    my $tempLog =shift();
    my @processedTempLog = process_temp_log($tempLog);
	my$minTempIndex =0;
	my$currMinTemp=$processedTempLog[0][6];
	
	foreach my $t (1..$#processedTempLog)
	{
		if($processedTempLog[$t][6]<$currMinTemp)
		{
			$currMinTemp = $processedTempLog[$t][6];
			$minTempIndex = $t;
		}
		
	}
	print "Minimum Celcius Temperature of $processedTempLog[$minTempIndex][6]";
	print " was at $processedTempLog[$minTempIndex][3]:$processedTempLog[$minTempIndex][4]:$processedTempLog[$minTempIndex][5]";
	print " on $processedTempLog[$minTempIndex][1]\\$processedTempLog[$minTempIndex][2]\\$processedTempLog[$minTempIndex][0]\n";

}

sub display_average_celsius_temp {
    my $tempLog =shift();
    my @processedTempLog = process_temp_log($tempLog);
	my $averageTemp=0;
	my $sumOfTemps=0;
	my $numOfTemps=0;
	
	foreach my $t (0..$#processedTempLog)
	{
		$sumOfTemps+=$processedTempLog[$t][6];
		$numOfTemps+=1;
	}
	$averageTemp = $sumOfTemps/$numOfTemps;
	print "Average Celcius Temperature from $processedTempLog[0][3]:$processedTempLog[0][4]:$processedTempLog[0][5]";
	print " on $processedTempLog[0][1]\\$processedTempLog[0][2]\\$processedTempLog[0][0]";
	print " to $processedTempLog[$#processedTempLog][3]:$processedTempLog[$#processedTempLog][4]:$processedTempLog[$#processedTempLog][5]";
	print " on $processedTempLog[$#processedTempLog][1]\\$processedTempLog[$#processedTempLog][2]\\$processedTempLog[$#processedTempLog][0]";
	print " is $averageTemp\n";
}

## tests

#process_temp_log($short_temp_log);

display_max_celsius_temp($short_temp_log);
display_min_celsius_temp($short_temp_log);
display_average_celsius_temp($short_temp_log);

display_max_celsius_temp($long_temp_log);
display_min_celsius_temp($long_temp_log);
display_average_celsius_temp($long_temp_log);
