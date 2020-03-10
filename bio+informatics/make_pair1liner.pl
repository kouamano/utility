#!/usr/bin/perl
while(<>){
	push(@arr,$_);
}
$arr = join('',@arr);
@arr = split(/Query=/,$arr);
shift(@arr);
$len = @arr;
$arr[$len-1] =~ s/Database: .*//s;


print "$arr[0]\n;;;\n";
print "$arr[$len-1]\n;;;\n";
