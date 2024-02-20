#!/usr/bin/perl
use strict;
use warnings;
my $transfered_bytes;
while ( <> ) {
	foreach my $temp (split(/ /,$_))
	{
		$transfered_bytes=$temp if ($temp =~/^\d/);
	}
	print $transfered_bytes;
}