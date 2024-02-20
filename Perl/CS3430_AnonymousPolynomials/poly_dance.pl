use strict;
use warnings;
use POSIX;


sub make_2nd_degree_poly { 
	my ($k2, $k1, $k0) = @_;

	return sub {my$a=$k2*$_[0]*$_[0]+$k1*$_[0]+$k0;		
		return "${k2}x^2 + ${k1}x + $k0 at x = $_[0] is $a\n";};
}

sub gen_2nd_deg_polys { 
	return map(make_2nd_degree_poly(@{$_}), @_);
}

sub apply_2nd_deg_polys2 {
	my @polys = @{$_[0]};
	my @numbers = @{$_[1]};
	my @app2nd;
	foreach my$n (@numbers)
	{
		foreach my$p (@polys)
		{
			@app2nd=(@app2nd, $p->($n));
		}
	}
	return @app2nd;
}

sub poly_dance {
	my @coeffs = @{$_[0]}; 
	my @numbers = @{$_[1]};
	my @polys = gen_2nd_deg_polys(@coeffs);
	my @poly_maps = apply_2nd_deg_polys2(\@polys, \@numbers);
	display_poly_maps(@poly_maps);
}

sub display_poly_maps{ 
	print " @_";
}

my @triplet0 = (1, 2, 3);
my @triplet1 = (4, 5, 6); 
#my @triplet2 = (7, 8, 9);
my @tripList = (\@triplet0, \@triplet1);#, \@triplet2);

#my $p1 = make_2nd_degree_poly(@triplet0);
#my $p2 = make_2nd_degree_poly(@triplet1);
#print $p1->(1);
#print $p2->(2);

my @numbers = (1..5);
poly_dance(\@tripList, \@numbers);
