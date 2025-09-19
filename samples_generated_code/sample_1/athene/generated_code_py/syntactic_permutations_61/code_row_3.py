import os

buffer_size = 1024
buffer = os.urandom(buffer_size)

while buffer:
    buffer = None
    break