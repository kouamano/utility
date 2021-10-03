#!/usr/bin/perl

# vars
$help = 0;
$check = 0;
$status = 0;
$cskip = 0;
$ig = 0;
$sf = 0;
$qf = "";
$ie = 0;
$head = "[^A-Za-z0-9]";
$tail = "[^A-Za-z0-9]";

# subroutine
sub _help {
	print "USAGE:\n";
	printf " match_lines.pl -c -h -s -i sf=<source file> qf=<query file>\n"
}

sub _check {
	print "ARGS:\n";
	print " help:$help:\n";
	print " check:$check:\n";
	print " status:$status:\n";
	print " ignore:$ig:\n";
	print " cskip:$cskip:\n";
	print " sf:$sf:\n";
	print " qf:$qf:\n";
}

sub _status {
	print "STATUS:\n";
	printf " Available.\n"
}

# argment analysis
foreach $l (@ARGV) {
	if($l eq "-h"){
		$help = 1;
	}elsif($l eq "-c"){
		$check = 1;
	}elsif($l eq "-s"){
		$status = 1;
	}elsif($l eq "-i"){
		$ig = 1;
	}elsif($l =~ /sf=(.*)/){
		$sf = $1;
	}elsif($l =~ /qf=(.*)/){
		$qf = $1;
	}elsif($l =~ /cskip=(.*)/){
		$cskip = $1;
	}else{
		print "unknown:$l:\n";
	}
}

# main
if($help == 1){
	&_help;
	$ie = 1;
}
if($check == 1){
	&_check;
	$ie = 1;
}
if($status == 1){
	&_status;
	$ie = 1;
}
if($ie == 1){
	exit(0);
}

## read query file
open(IN,$qf);
while(<IN>){
	chomp;
	push(@arr,$_);
}
close(IN);

if($ig == 0){
## read source file
	open(IN,$sf);
	while(<IN>){
		chomp;
		$sl = $_;
		@target = split(/\t/,$sl);
		for($i=0;$i<$cskip;$i++){
			shift(@target);
		}
		$target = join('',@target);
		print $sl;
		print "\t<\t>\t";
		foreach(@arr){
			if($target =~ /($head)($_)($tail)/){
				print "\t$_";
			}
		}
		print "\n";
	}
	close(IN);
}else{
## read source file
	open(IN,$sf);
	while(<IN>){
		chomp;
		$sl = $_;
		@target = split(/\t/,$sl);
		for($i=0;$i<$cskip;$i++){
			shift(@target);
		}
		$target = join('',@target);
		print $sl;
		print "\t<\t>\t";
		foreach(@arr){
			if($target =~ /($head)($_)($tail)/i){
				print "\t$_";
			}
		}
		print "\n";
	}
	close(IN);
}
