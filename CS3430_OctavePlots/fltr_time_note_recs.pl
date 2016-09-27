#!/usr/bin/perl
use strict;
use warnings;

while ( <> ) {
	foreach my $temp (split(//,$_))
	{
		if($temp=~/-/||$temp=~/_/)
		{
			print "\t";
		}
		else
		{
			print $temp;
		}
	}
	
}