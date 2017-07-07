#!/bin/sh

for i in `seq -w 1 50`
	do echo chwolf$i:11$i:1100::0:0:aufgabe3:/usr/home/chwolf$i:/bin/sh:`openssl rand -base64 6` >> usrDATA.txt
done

