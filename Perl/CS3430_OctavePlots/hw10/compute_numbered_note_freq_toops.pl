#!/usr/bin/perl

use strict;
use warnings;

my %A440_NOTE_NUMBERS = (
    'A0',  1,
    'A0#', 2,
    'B0',  3,
    'C1',  4,
    'C1#', 5,
    'D1',  6,
    'D1#', 7,
    'E1',  8,
    'F1',  9,
    'F1#', 10,
    'G1',  11,
    'G1#', 12,
    'A1',  13,
    'A1#', 14,
    'B1',  15,
    'C2',  16,
    'C2#', 17,
    'D2',  18,
    'D2#', 19,
    'E2',  20,
    'F2',  21,
    'F2#', 22,
    'G2',  23,
    'G2#', 24,
    'A2',  25,
    'A2#', 26,
    'B2',  27,
    'C3',  28,
    'C3#', 29,
    'D3',  30,
    'D3#', 31,
    'E3',  32,
    'F3',  33,
    'F3#', 34,
    'G3',  35,
    'G3#', 36,
    'A3',  37,
    'A3#', 38,
    'B3',  39,
    'C4',  40,
    'C4#', 41,
    'D4',  42,
    'D4#', 43,
    'E4',  44,
    'F4',  45,
    'F4#', 46,
    'G4',  47,
    'G4#', 48,
    'A4',  49,
    'A4#', 50,
    'B4',  51,
    'C5',  52,
    'C5#', 53,
    'D5',  54,
    'D5#', 55,    
    'E5',  56,
    'F5',  57, 
    'F5#', 58, 
    'G5',  59,
    'G5#', 60,     
    'A5',  61,
    'A5#', 62,     
    'B5',  63, 
    'C6',  64, 
    'C6#', 65, 
    'D6',  66, 
    'D6#', 67, 
    'E6',  68, 
    'F6',  69, 
    'F6#', 70, 
    'G6',  71, 
    'C6#', 72, 
    'A6',  73, 
    'A6#', 74, 
    'B6',  75,
    'C7',  76,
    'C7#', 77,
    'D7',  78,
    'D7#', 79,
    'E7',  80,
    'F7',  81,
    'F7#', 82,
    'G7',  83,
    'G7#', 84,
    'A7',  85,
    'A7#', 86,
    'B7',  87,
    'C8',  88,
    );

my %note_freqs_table;
while ( <> ) {
    ## your code
}

sub display_numbered_note_freqs_table {
    my %notes_freq_table = @_;
    while ( my($note, $freq) = each(%notes_freq_table) ) {
	if ( exists($A440_NOTE_NUMBERS{$note}) ) {
	    print "$A440_NOTE_NUMBERS{$note}\t$freq\n";
	}
	else {
	    die('Unknown note: ' . $note);
	}
    }
}


display_numbered_note_freqs_table(%note_freqs_table);
