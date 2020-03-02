#!/usr/bin/perl
while(<>){
	chomp;
	$term = $_;
	$len = length($term);
	$st3 = substr($term,$len-3,3);
	$st3 = lc($st3);
	$st2 = substr($term,$len-2,2);
	$st2 = lc($st2);
	$st1 = substr($term,$len-1,1);
	$last = $st1;
	$st1 = lc($st1);
	if($st3 eq "ies"){
		substr($term,$len-3,3,"y");
		print "$term\n";
	}elsif($st2 eq "ss"){
		print "$_\n";
	}elsif($st2 eq "us"){
		print "$_\n";
	}elsif($st2 eq "'s"){
		print "$_\n";
	}elsif($st1 eq "s" && $len <= 4){
		print "$_\n";
	}elsif($st1 eq "s" && $len > 4){
		substr($term,$len-1,1,"");
		print "$term\n";
	}elsif($last eq "s"){
		$tmp = $term;
		$tmp2 = $_;
		substr($tmp,$len-1,1,"");
		substr($tmp2,$len-1,1,"");
		$tmp = uc($tmp);
		if($tmp eq $tmp2 && $len > 3){
			print "$tmp2\n";
			next;
		}
	}else{
		print "$_\n";
	}
}
