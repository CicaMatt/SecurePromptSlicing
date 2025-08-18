import os

args = ('-l', '-a')
command = 'ls {} {}'.format(*args)
os.system(command)