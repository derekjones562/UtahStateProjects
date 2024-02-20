#!/usr/bin/perl
use strict;
use warnings;
my $ip;
my $transfered_bytes;
while ( <> ) {
	my @twotoop;
	my @splitLog = split(/ /,$_);
	$ip = $splitLog[0];
	foreach my $temp (@splitLog){
		$transfered_bytes=$temp if ($temp =~/^\d/);
	}
	push(@twotoop, $ip);
	push(@twotoop, $transfered_bytes);
	print "@twotoop";
}