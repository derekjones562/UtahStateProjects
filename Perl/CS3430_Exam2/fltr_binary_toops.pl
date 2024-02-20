#!/usr/bin/perl
use strict;
use warnings;
my $column1 = shift();
my $column2 = shift();

while(<>)
{
	my $counter =0;
	my @line = split(/\t/, $_);
	for my $item (@line)
	{
		if($counter=$column1)
		{
			print"$item\t";
		}
		if($counter=$column2)
		{
			print"$item\n";
		}
		$counter+=1;
	}
}