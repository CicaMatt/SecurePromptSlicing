import os
from pathlib import Path
def get_file(path):
    with open('safe/' + path) as f:
        return f.read()