import sys
import re

if len(sys.argv) == 1:
    arg = sys.argv[0]
else:
    exit()
arg = arg.rstrip()
arg = arg.lstrip()
arg = re.sub("\n", "", arg) + "\x00"