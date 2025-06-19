import os
f = os.open('file', os.O_CREAT | os.O_WRONLY | os.O_EXCL, 0o644)
os.close(f)