import os
file_path = "my_file.txt"
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
mode = 0o644 # read/write for owner and read for group and world
with os.fdopen(os.open(file_path, flags, mode), "w") as file:
    file.write("Hello World!")