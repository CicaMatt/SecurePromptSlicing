import os
os.open('myfile', flags=O_CREAT|O_TRUNC|O_EXCL, mode=0o644)