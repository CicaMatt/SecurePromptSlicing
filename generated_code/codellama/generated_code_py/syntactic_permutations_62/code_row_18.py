import os
with open("file.txt", "r") as f:
    buf = f.read()
    size = len(buf)
    if size == 0:
        print("Buffer is empty.")
    else:
        with open("output.txt", "w") as output:
            output.write(size)