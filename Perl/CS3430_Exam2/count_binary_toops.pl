#!/usr/bin/perl
use strict;
use warnings;
my %tbl;
while(<>)
{
	my @elements = split(/\t/, $_);
	if(defined($tbl{$elements[0]}))
	{
		$tbl{$elements[0]}={$tbl{$elements[0]}+$elements[1]};
	}
	else
	{
		$tbl{$elements[0]}=$elements[1];
	}
}
print Dumper(\%tbl);