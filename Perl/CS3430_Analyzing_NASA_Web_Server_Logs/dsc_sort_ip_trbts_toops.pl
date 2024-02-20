#!/usr/bin/perl
use strict;
use warnings;
my@listoftoops;
while(<>){
	my @compare = split(/\s/,$_);
	my $position =0;
	foreach (@listoftoops)
	{
		my @toop = split(/\s/, $listoftoops[$position]);
		if($toop[1] > $compare[1]){
			$position++;
		}
		else{
			last;
		}
	}
	splice (@listoftoops,$position,0, $_);
}
print @listoftoops;