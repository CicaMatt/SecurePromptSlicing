import os

file = "test.txt"

fd = os.open(file, os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)