import os

f = os.open("testfile", os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)
print(f)