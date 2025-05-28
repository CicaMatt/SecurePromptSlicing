import os
 
fd = os.open('test.txt', os.O_CREAT | os.O_TRUNC | os.O_WRONLY, 0o644)
os.write(fd, 'Hello World')
os.close(fd)