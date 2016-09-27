#!/usr/bin/perl
use strict;
use warnings;
my @top5;
while(<>){
	push(@top5, $_);
	last;
}
while(<>){
	#if the input is unsorted numbers use this for sorting and only getting the top 5
	#print "s:$_";
	#my $i=0;
	#foreach my$value (@top5){
	#	if($_>$value){
	#		splice(@top5,$i,0, $_);
	#		last;
	#	}
	#	$i+=1;
	#}
	push (@top5, $_) if ($#top5<5);
	while($#top5>=5){
		pop @top5;
	}
}
print @top5;