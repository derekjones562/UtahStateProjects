#!/usr/bin/perl
use strict;
use warnings;
my $outfile = shift();
open(my$out, '>', $outfile) or die "couldnt open file";
print $outfile, "\n";
print $out "Y=[\n";
while(<>)
{
	my @toop =split(/\s/,$_);
  	print $out "\t",$toop[1],",\n";
}
print $out "];
figure;
bar(Y, 'FaceColor', [0, 0.5, 0.5],
'EdgeColor', [0, 0.5, 0.5],
'LineWidth', 2);
title('A440 Note Frequencies');";
close $out;