#!/usr/bin/perl
$file = $ARGV[0];
$head = $ARGV[1];
$count = 1;
open(IN,$file);
while(<IN>){
	if($_ =~ /^>/){
		$_ =~ s/^>//;
		$_ =~ s/^\s+//;
		$_ =~ s/\s+$//;
		$_ =~ s/\s/_/g;
		print ">gi|";
		print "${count}|ref|${count}.1|$head\n";
		#print "$_\n";
		$count++;
	}else{
		print $_;
	}
}
close(IN);
