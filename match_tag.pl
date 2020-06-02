#!/usr/bin/perl

$src = $ARGV[0];	#fixed lines
$target = $ARGV[1];	#valiable lines

%match = ();
open(IN,$target);
while(<IN>){
	chomp;
	$match{$_} = 1;
}
close(IN);

open(IN,$src);
while(<IN>){
	chomp;
	if($match{$_} == 1){
		print "1 ";
	}else{
		print "0 ";
	}
}
close(IN);

print "\n";
