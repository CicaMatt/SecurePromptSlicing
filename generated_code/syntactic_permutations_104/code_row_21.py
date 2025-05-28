import os
from os import path
try:
  fd = os.open(path, os.O_RDWR | os.O_CREAT)
except OSError as e:
  print("An error occurred while opening or creating the file.")
else:
  print("The file was successfully opened and created.")