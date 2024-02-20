#!/usr/bin/perl

###################################################
## bee_music.pl
###################################################

use strict;
use warnings;
use FileHandle;

sub grep_files {
    my ($dir, $pat) = @_;
    opendir(my $dir_handle, $dir) or die $!;
    my @files = grep { $_ =~ /$pat/ } readdir($dir_handle);
    closedir($dir_handle);
    return @files;
}
## generate a no_play file
sub gen_no_play_file {
    my $filepath = $_[0];
    my@noplayfile= split (/\./, $filepath);
    open(IN,'<', $filepath)or die "couldnt open".$filepath."\n";
    open(NOPLAYOUT,'>', $noplayfile[0]."_no_play.txt")or die "can write to file\n";
    #print OUT "test";
    <IN>;
    while(<IN>)
    {
    	if($_!~/^\s/)
    	{
    		my$index=2;
	    	my @s = split(/\[/,$_);
	    	if($s[1]=~/\w/)
	    	{
	    		$index=1;
	    	}
	    	my @notes=split(/\]/, $s[$index]);
	    		print NOPLAYOUT "$notes[0]\n";
    	}
    }
    close (IN);
    close(NOPLAYOUT);
}

sub merge_bee_music_files_for_freq {
    my ($freq, $bee_music_dir, $bee_music_merged_file) = @_;
    
	
    if ( $freq == 44100 || $freq == 22050 || $freq == 11025 || $freq == 5512 ) {
		my $datePat="\\d{4}-\\d{2}-\\d{2}";
		my $timePat="\\d\\d-\\d\\d-\\d\\d";
		my$line_pat = "$datePat\_$timePat\_$freq\_logo\.txt";
		#print $bee_music_dir;
		##opendir(IN,$bee_music_dir)or die "directory not found\n";
		##while(readdir(IN))
		##{
		##	if($_ =~/$line_pat/)
		##	{
		##		print $_,"\n";
		##	}
		##}
		my@files =grep_files($bee_music_dir,$line_pat);
		#print "$files[0]\n";
		open(OUT, '>', $bee_music_merged_file);
		my$flag=1;
		foreach my $i(@files)
		{
			gen_no_play_file($bee_music_dir."$i");
			open(IN, '<', $bee_music_dir."$i")or die "couldnt open dir:".$bee_music_dir."\n";
			$_= <IN>;
			if($flag!=0)
			{
				print OUT $_;
				$flag=0;
			}	
			while($_= <IN>)
			{
				if($_!~/^\s/)
				{
					print OUT $_;
				}
				
			}
			close(IN);
		}
    }
    else {
	print "Unknown frequency $freq\n";
    }
    close(OUT);
}
##def regex
##my $datePat="\\d{4}-\\d{2}-\\d{2}";
##my $timePat="\\d\\d-\\d\\d-\\d\\d";
##my$line_pat = "$datePat\_$timePat\_\\d{4,6}\_logo\.txt";

## Uncomment the next three prints when debugging
$ARGV[0] = 44100;
$ARGV[1] ="real_data/";
$ARGV[2] =$ARGV[1]."merged_".$ARGV[0].".txt";
#print $ARGV[0], "\n";
#print $ARGV[1], "\n";
#print $ARGV[2], "\n";
## get three command line arguments from the user and go
merge_bee_music_files_for_freq($ARGV[0], $ARGV[1], $ARGV[2]);
#my$filename="pl_test_data/2015-08-15_15-41-32_22050_logo.txt";
#gen_no_play_file($filename);

