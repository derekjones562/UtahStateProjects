use strict;
use warnings;
use POSIX;


##561,1105,1729,2465,2821,6601,8911,10585,15841,29341,41041 ,46657 ,52633 ,62745 ,63973 ,75361,101101 ,115921 ,126217 ,162401 ,172081 ,188461 ,252601 ,278545 ,294409,314821 ,334153 ,340561 ,399001 ,410041 ,449065 ,488881 ,512461 ,530881 ,552721 
##All of the numbers passed the fermat test
##none of the numbers passed the is_prime test. this is because the is_prime tests each number lower than it and uses the mod function. the fermat test has a few numbers that 'slip past' it. these numbers are the carmichael numbers.
sub is_square_free {
	my $n = $_[0];
	if ($n == 1 || $n == -1) {
		return 1;
	}
	for(my $d = 2; $d <= ceil(sqrt($n)) + 1; $d++) {
		if ( $n % ($d*$d) == 0 ) {
			return 0;#return false
		}
	}
	return 1;
}
sub is_prime {
	my $n = $_[0];
	my $d = 2;

	#print("in is_prime. n=", $n,"\n");
	while($d != $n)
	{
		
		#print("n=", $n,"\nd=", $d, "\n");
		if(($n % $d)==0)
		{
			return 0;
		}
		
		
		$d++;
		if($d != $n)
		{
			if($d % 2 ==0)
			{
				if($d != 2)
				{
					$d++;
				}
			}
		}
	}
	#print("$n is prime\n");
	return 1;

}
sub find_prime_divisors{
	my $n = $_[0];
	my @prime_divisors;
	for (my$d = 2; $d < $n; $d++)
	{
		#print("\n$n%$d=", $n % $d);
		if($n % $d==0)
		{
			#print("\n$d=", $d);
			if(is_prime($d))
			{
				#print("in find_prime_divisor. ", $d, " is prime\n");
				@prime_divisors = (@prime_divisors, $d);#add to list
				#print("prime_divisors = ", @prime_divisors, "\n");
			}
		}
	}
	#print (@prime_divisors, "\n");
	return @prime_divisors;
	#return list
}

sub korselts {
	my $n = shift();
	my @divisorList = @_;
	my $p;

	my $f = 0;
	#print "@divisorList \n";
	for( my $d=0; $d <= $#divisorList; $d++)
	{
		#print ("inforloop\n");
		$f=1;
		$p = $divisorList[$d];
		#print("p=", $p, "\n");
		if((($n-1)%($p-1))!=0)
		{
			return 0;
		}
	}
	if($f==0)
	{
		return 0;
	}

	return 1;
}
sub is_carmichael{
	my $n = $_[0];
	if(is_square_free($n))
	{
		#print($n, " in is_carmichael and passed is square free\n");
		my @divisorList = find_prime_divisors($n);
		#print "@divisorList \n";
		if(korselts($n ,@divisorList))
		{
			return 1;
		}
	}
	else
	{
		#print("not sqare free\n");
		return 0;
	}
}

my@carmichael_list;
my$num_found=0;
for(my $i=0; $num_found<34; $i++)
{
		#print("\n", $i," ");
	if(is_carmichael($i))
	{
		@carmichael_list = (@carmichael_list, $i);
		#print ($i, " is carmichael\n");
		$num_found++;	
	}

}
for(my $i=0; $i<=$#carmichael_list; $i++)
{
	print($carmichael_list[$i], "\n");
}

