#!/bin/bash
## declare, allocate, assign
sym=$1
declare -a ldarray=()
declare -a syarray=()

## search ldconfig
src="ldconfig"
ldarray=`ldconfig  -p | awk -F' => ' '{print $2}'`
for e in ${ldarray[@]}; do
  #echo :::${e}:::
  syarray=`nm ${e} | grep $sym`
    IFS=$'\n'
    for s in ${syarray}; do
      echo ${e}::: ${s}
    done
done

