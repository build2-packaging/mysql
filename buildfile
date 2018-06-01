# file      : buildfile
# copyright : Copyright (c) 2016-2018 Code Synthesis Ltd
# license   : GPLv2 with FOSS License Exception; see accompanying COPYING file

./: {*/ -build/} doc{COPYING GPLv2 INSTALL README} manifest

# Don't install tests or the INSTALL file.
#
tests/:          install = false
doc{INSTALL}@./: install = false
