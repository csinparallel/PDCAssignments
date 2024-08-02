#/bin/bash
#
# shell script to generate pin-hashes
#
# Usage: ./genHash 99999999
#        ./genHash 12345678

ARG=$1
ARG_LENGTH=${#ARG}

if [ $ARG_LENGTH -gt 0 ]
then
	echo -n $1 | md5sum
else
	echo "Usage: ./genHash <8-digit-pin>"
fi

