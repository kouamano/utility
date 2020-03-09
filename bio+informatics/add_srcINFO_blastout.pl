#!/usr/bin/perl
$dbseq = $ARGV[0];
$blastres = $ARGV[1];
%hs=();
open(IN,$dbseq);
while(<IN>){
	if($_ =~ /^>/){
		#chomp;
		@arr=();
		@arr = split(/\|/,$_);
		$len = @arr;
		$line = "$arr[$len-2]"."\.1";
		$hs{$line} = $_;
	}
}
close(IN);

open(IN,$blastres);
while(<IN>){
	if($_ =~ /^>/){
		chomp;
		@arr=();
		@arr = split(/\|/,$_);
		$ref = "$arr[1]";
		print $hs{$ref};
		print $_;
	}else{
		print $_;
	}
}
close(IN);
