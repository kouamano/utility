#!/usr/bin/perl
while(<>){
	chomp;
	$term = $_;
	$len = length($term);
	$st = substr($term,$len-3,3);
	$st = lc($st);
	if($st eq "ies"){
		substr($term,$len-3,3,"y");
		print "$term\n";
	}
}
