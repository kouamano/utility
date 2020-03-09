#!/usr/bin/perl
$dbseq = $ARGV[0];
$blastres = $ARGV[1];
%hs=();
open(IN,$dbseq);
while(<IN>){
	if($_ =~ /^>/){
		@arr=();
		@arr = split(/\|/,$_);
		$len = @arr;
		$line = "$arr[$len-2]"."\.1";
		#print "$line\n";
		$hs{$line} = $_;
	}
}
close(IN);
print $hs{'123.1'};

open(IN,$blastres);
while(<IN>){
	if($_ =~ /^>/){
		$ref = $_;
		$ref =~ s/.[^\|]+\|//;
		print $ref;
	}else{
		print $_;
	}
}
close(IN);

