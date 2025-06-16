import os
with open('myfile', 'w') as f:
    pass # write something to the file here
f = os.open('myfile2', os.O_CREAT | os.O_TRUNC | os.O_WRONLY)
os.close(f)