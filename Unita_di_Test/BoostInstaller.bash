#!/bin/bash

#TESTED

#references:
#http://www.boost.org/doc/libs/1_54_0/more/getting_started/unix-variants.html

#installa boost una libreria comprendente tante cose interessanti

echo "******************* BOOST INSTALLER ***************************"
echo "PURPOSE"
echo "boost è utile per usare CUTE in Eclipse per implementare test suite in C++."


#reperimento di boost:
wget -O file.tar.gz --progress=bar http://downloads.sourceforge.net/project/boost/boost/1.54.0/boost_1_54_0.tar.gz?r=http%3A%2F%2Fwww.boost.org%2Fusers%2Fhistory%2Fversion_1_54_0.html&ts=1380891258&use_mirror=garr

tar -xvf  file.tar.gz
rm file.tar.gz
sudo mv boost_1_54_0 /opt/.

#eventualmente ora bisogna compilare

echo "FINE"


