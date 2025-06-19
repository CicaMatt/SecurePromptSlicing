import os

file = 'example.txt'
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
mode = 0o664
with open(file, flags) as f:
    f.write('Hello World!')