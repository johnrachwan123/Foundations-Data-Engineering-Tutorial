#!/usr/bin/env bash

set () {
echo "$1,$2" >> database
}
get () {
#grep " ^$1 ," database | tail -n 1 | sed -e "s /^ $1 ,// "
grep "^$1," database | tail -n 1 | cut -f 2 -d ','
}
$1 "$2" "$3"
