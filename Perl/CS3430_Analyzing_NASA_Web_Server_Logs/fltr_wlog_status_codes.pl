#!/usr/bin/perl
use strict;
use warnings;
my $code = shift();
while(<>)
{
	my @splitLog = split(/ /,$_);
	if($splitLog[8]=~$code)
	{
		print $_;
	}
}