#!/usr/bin/perl

## Derek Jones
## A00974024

use warnings;
use strict;
use List::Util qw( min ); ## min function in case you need it;

my $short_text_1 = 'ab';
my $short_text_2 = 'aaa, bb c';
my $short_text_3 =
'
aaaaa, bbbb ccc;
dd e!
';

my $rumi_quote_1 = 'The wound is the place where the Light enters you.';
my $rumi_quote_2 = '
Don\'t grieve.
Anything you lose comes round
in another form.
';

my $rumi_quote_3 = 'Sell your cleverness and buy bewilderment.';
my $rumi_quote_4 = '
Raise your words, not voice.
It is rain that grows flowers, not thunder.
';

my @alphabet = ('a', 'b', 'c', 'd', 'e',
'f', 'g', 'h', 'i', 'j',
'k', 'l', 'm', 'n', 'o',
'p', 'q', 'r', 's', 't',
'u', 'v', 'w', 'x', 'y', 'z');

## PL Problem 1 (5 points)
sub countfrequencies
{
	my $mystring =shift();
	my$testletter =shift();
	my $count=0;
	#print "mystring = $mystring \n";
	#print "testletter = $testletter \n";
	
	my @splitmystring= split(//, $mystring);
	foreach my$i (0..$#splitmystring)
	{
		if($splitmystring[$i]=~$testletter)
		{
			$count++;
		}
	}
	my @wordFrequency;
	push(@wordFrequency,$testletter);
	push(@wordFrequency, $count);
	
	return \@wordFrequency;
}
sub inarray
{
	my@letterList=shift();
	my$l=shift();
	foreach my$i (@letterList)
	{
			print "i=@{$i}\n";
			foreach my$j (@{$i})
			{
				print"j=$j\n";
				if($j=~/[[:alpha:]]/)
				{
					print "$j==$l\n";
					if(lc($j)=~$l)
					{
						print "return true\n";
						return 1;
					}
				}
			}
	}
	return 0;
}
sub sortfrequencies
{
	
}
sub display_top_freq_chars {
    print '-----------', "\n";
    print $_[0], "\n";
    my $txt = shift();
	my $n= shift();
	my @letterList;
	my @splitTxt = split(//, $txt);
	my$i=0;
	if(($splitTxt[$i]=~/w/))
	{
		print"splittxt= $splitTxt[$i]\n";
		$i++;}
	push(@letterList, countfrequencies($txt,lc($splitTxt[$i])));
	foreach my$letter (1..$#splitTxt)
	{
		foreach my$u (@letterList)
		{
		print "letterlist= @{$u}\n";
		}
		print"splittext=$splitTxt[$letter]\n";
		print "letter=$letter\n";
		if(!inarray(@letterList, lc($splitTxt[$letter])))
		{
			push(@letterList, countfrequencies($txt,lc($splitTxt[$letter])));
		}
		
	}
	sortfrequencies(\@letterList);
	foreach my$n2 (0..$n-1)
	{
		#print"n2=$n2\n";
		my$count=0;
		foreach my$s (@{$letterList[$n2]})
		{
			if($count==0)
			{
				#print "$s-->";
				$count++;
			}
			else
			{
				#print"$s\n";
				$count=0;
			}
		}
		#print"@{$letterList[$n2]}\n";
	}
	
}

## Tests for PL Problem 1
#display_top_freq_chars($short_text_1, 2);
display_top_freq_chars($short_text_2, 3);
#display_top_freq_chars($short_text_3, 3);
#display_top_freq_chars($rumi_quote_1, 4);
#display_top_freq_chars($rumi_quote_2, 5);
#display_top_freq_chars($rumi_quote_3, 6);
#display_top_freq_chars($rumi_quote_4, 7);