import os

try:
    fd = os.open("newfile", os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL, 0o644)
except OSError as e:
    print('Failed to open file: %s' % e)
else:
    with os.fdopen(fd, 'w') as f:
        f.write("Hello World")