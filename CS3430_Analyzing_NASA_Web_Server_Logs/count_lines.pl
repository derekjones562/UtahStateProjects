#!/usr/bin/perl
use strict;
use warnings;
my $line_count = 0;
while ( <> ) { 
	$line_count++ if ( $_ =~ /\S+/ ); 
}
print $line_count, "\n";