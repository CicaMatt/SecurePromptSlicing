import os

# Open a file with O_CREAT, O_TRUNC, O_WRONLY, and O_EXCL flags
fd = os.open("example.txt", os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)

# Close the file descriptor
os.close(fd)