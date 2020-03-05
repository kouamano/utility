#!/usr/bin/perl
$count = 0;
while(<>){
	if($_ =~ /^>/){
		$count++;
		chomp;
		print "$_|$count";
	}else{
		print $_;
	}
}
