import os
import sys
fd = os.open('test', os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL, 0o644)
if fd == -1:
    print("Open failed")
else:
    print("Open success")
    os.close(fd)