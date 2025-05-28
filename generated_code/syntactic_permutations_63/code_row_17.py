import os

buffer = ''
number_of_bytes = 0

with open(path, 'rb') as f:
    buffer = f.read()

if len(buffer) == 0:
    number_of_bytes = 0
else:
    number_of_bytes = os.stat(path).st_size

with open(output_file, 'wb') as f:
    f.write(str(number_of_bytes))