# file      : buildfile
# license   : GPLv2 with Universal FOSS Exception; see accompanying LICENSE file

# Glue buildfile that "pulls" all the packages.

import pkgs = {*/ -upstream/}
./: $pkgs
