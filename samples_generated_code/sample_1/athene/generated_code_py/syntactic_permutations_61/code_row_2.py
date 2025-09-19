import os

buffer_size = 1024
buffer = os.urandom(buffer_size)

for _ in range(10):
    buffer = None