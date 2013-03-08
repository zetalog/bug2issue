#!/bin/sh

usage()
{
	echo "Usage: `basename $0`"
	echo " [-d] [-e bug2issue]"
	echo " [-s status] [-f field] [-p product] [-t]"
	echo " <gitrepo> <gituser> <bughost> <bugdb> <buguser>"
	echo "Where:"
	echo "       -d: dry run"
	echo "       -e: specify bug2issue executable path"
	echo "       -t: append bug id to the issue title"
	echo "       -s: specify matched bug status to close issue"
	echo "       -f: specify bug field to convert whose values into issue labels"
	echo "       -p: specify product to convert whose component values into issue labels"
	echo "  gitrepo: specify github repo name, ex. zetalog/bug2issue"
	echo "  gituser: specify github user information, ex. zetalog:secret"
	echo "  bughost: specify bugzilla database host:port information, ex. localhost:3306"
	echo "    bugdb: specify bugzilla database name, ex. bugzilla"
	echo "  buguser: specify bugzilla database user information, ex. root:secret"
	exit 1
}

fulldir()
{
	lpath=$1
	(
		cd $lpath; pwd
	)
}

getdir()
{
	lpath=`dirname $1`
	fulldir $lpath
}

MINOPTS=5
UPLDFLAGS=-ac
ENUMFLAGS=-l
SCRIPT=`getdir $0`
BUG2ISSUE=$SCRIPT/bug2issue

while getopts "de:s:f:p:t" opt
do
	case $opt in
	d) DRYRUN="yes";;
	e) BUG2ISSUE=`getdir $OPTARG`/bug2issue;;
	s) UPLDFLAGS="$UPLDFLAGS -s $OPTARG";;
	f) UPLDFLAGS="$UPLDFLAGS -l $OPTARG";;
	p) UPLDFLAGS="$UPLDFLAGS -n $OPTARG";;
	t) UPLDFLAGS="$UPLDFLAGS -t";;
	?) echo "Invalid argument $opt"
	   usage;;
	esac
done
shift $(($OPTIND - 1))

if [ $# -lt $MINOPTS ]; then
	echo "Not enough parameters, $# < $MINOPTS."
	usage
fi

if [ "x$1" = "x" ]; then
	echo "Please specify a full path to bug2issue."
	usage
fi


UPLDFLAGS="$UPLDFLAGS -r $1 -w $2 -h $3 -d $4 -u $5"
ENUMFLAGS="$ENUMFLAGS -h $3 -d $4 -u $5"

bugs=`$BUG2ISSUE $ENUMFLAGS`

for bug_id in $bugs; do
	if [ "x$DRYRUN" = "xyes" ]; then
		echo $BUG2ISSUE -b $bug_id $UPLDFLAGS
	else
		eval $BUG2ISSUE -b $bug_id $UPLDFLAGS
	fi
done

