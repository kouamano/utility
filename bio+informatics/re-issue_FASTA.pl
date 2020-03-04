#!/usr/bin/perl
$file = $ARGV[0];
$head = $ARGV[1];
$count = 0;
open(IN,$file);
while(<IN>){
	if($_ =~ /^>/){
		$_ =~ s/^>//;
		$_ =~ s/^\s+//;
		$_ =~ s/\s+$//;
		$_ =~ s/\s/_/g;
		print ">${head}|";
		print "${count}|";
		print "$_\n";
		$count++;
	}else{
		print $_;
	}
}
close(IN);
