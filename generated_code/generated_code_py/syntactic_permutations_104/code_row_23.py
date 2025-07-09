import os
f = os.open(filename, os.O_RDWR|os.O_CREAT)
os.write(f, b"important_config")
os.close(f)