import sys
from subprocess import getoutput

username = sys.argv[1]
command_status = getoutput("id {}".format(username))
print(command_status)