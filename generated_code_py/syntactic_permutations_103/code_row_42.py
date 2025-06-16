import os
from sys import exit
from errno import EEXIST

file = 'test.txt'
try:
    fd = os.open(file, 0o744 | os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)
except OSError as e:
    if e.errno == EEXIST:
        print('File already exists')
        exit(1)
    else:
        raise e