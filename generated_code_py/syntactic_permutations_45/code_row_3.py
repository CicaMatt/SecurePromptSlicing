import os
from pathlib import Path

def read_file(filename):
  with open(Path('safe') / filename) as f:
    return f.read()