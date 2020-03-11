#!/usr/bin/perl
while(<>){
	push(@arr,$_);
}
$arr = join('',@arr);
@arr = split(/Query=/,$arr);
shift(@arr);
$len = @arr;
$arr[$len-1] =~ s/Database: .*//s;
foreach(@arr){
	$Q = $_;
	@Q = split(/>/s,$Q);
	$H = shift(@Q);
	"" =~ //;
	$H =~ /([^\n]+)\n/;
	$h = $1;
	$h =~ s/\s//g;
	foreach(@Q){
		#print $_;
		@hit = split(/\n/,$_);
		$dbentry = shift(@hit);
		$dbentry =~ s/\s/_/g;
		$hit = join(/ ;; /,@hit);
		print " $dbentry ;; ";
		print " $h ;; ";
		print "$hit";
		print ";;;\n";
	}
}
