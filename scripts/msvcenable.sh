#!/bin/sh

usage()
{
	echo "Usage: `basename $0` [-c] [-d] [-p] [-r] <srcdir>"
	echo "Where:"
	echo "    -c: enable C source codes convertion"
	echo "    -d: dry run"
	echo "    -p: enable Lex/Yacc source codes convertion"
	echo "    -r: reverse conversion - dos2unix, default unix2dos"
	echo "srcdir: source code directory contained dsp/dsw"
	exit 0
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

while getopts "cdpr" opt
do
	case $opt in
	c) CLANGUAGE="yes";;
	d) DRYRUN="yes";;
	p) PARSER="yes";;
	r) REVERSE="yes";;
	?) echo "Invalid argument $opt"
	   usage;;
	esac
done
shift $(($OPTIND - 1))

SCRIPT=`getdir $0`

if [ "x$1" = "x" ]; then
	echo "source directory is not specified."
	usage
fi

SRCDIR=`fulldir $1`

if [ "x$REVERSE" = "xyes" ]; then
	CONVERT=dos2unix
else
	CONVERT=unix2dos
fi

convert_one()
{
	find . -name $1 | grep -v .pc | xargs $CONVERT
}

convert_all()
{
	convert_one *.dsp
	convert_one *.dsw
	if [ "x$PARSER" = "xyes" ]; then
		convert_one *.l
		convert_one *.y
	fi
	if [ "x$CLANGUAGE" = "xyes" ]; then
		convert_one *.h
		convert_one *.c
	fi
}

(
	cd $SRCDIR
	convert_all
)

