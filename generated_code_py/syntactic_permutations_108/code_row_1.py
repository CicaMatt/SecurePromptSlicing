import sys
import os
def execute(user):
    cmd = 'getent passwd {}'.format(user)
    output = os.popen(cmd).read()
    return output