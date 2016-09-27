#!/usr/bin/perl
use strict;
use warnings;
##no warnings 'recursion';
sub randint {
my ($a, $b) = @_;
return int($a + rand($b-$a+1));
}
sub is_even { return $_[0] % 2 == 0; }
sub square { return $_[0]**2; }
sub expmod {
	my ($b, $e, $m) = @_;
	if($e == 0){
		return 1;
	}
	elsif(is_even($e)){
		my $expm = expmod($b, $e/2, $m);
		return ($expm*$expm)%  $m;
	}
	else{
		return ($b*expmod($b, $e-1, $m))% $m;
	}
}

sub fermat_test {
	my $n = $_[0];
	
	my $a;
	if($n<3){
		if ($n == 2){
			return 1;##return true
		}
		$a=2;
	}
	else{
		$a= randint(2,$n-1);
	}
	return expmod($a,$n,$n)==$a;
}

sub is_fermat_prime {
	my ($n, $times) = @_;
	if($times <= 0){
		return 1;##return true
	}
	elsif(fermat_test($n)){
		return is_fermat_prime($n, $times-1);
	}
	else{
		return 0;##return false
	}
}


## you can use this subroutine to test your code
sub sum_of_fermat_primes {
my $n = $_[0];
my $sum = 0;
for(my $i = 0; $i <= $n; $i++) {
	if ( is_fermat_prime($i, 20) ) {
		$sum += $i;
	}

}
return $sum;
}
my$n=552721;#test a single number
if(is_fermat_prime(561,20))
{
print $n, " is prime\n";
}

print 'my sum =', sum_of_fermat_primes(10), "\n";
print 'my sum =', sum_of_fermat_primes(20), "\n";
print 'my sum =', sum_of_fermat_primes(560), "\n";
print 'my sum =', sum_of_fermat_primes(570), "\n";