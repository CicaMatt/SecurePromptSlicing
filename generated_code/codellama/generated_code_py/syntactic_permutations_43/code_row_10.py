import os
import sys
def get_file(file_path):
    return open(os.path.join(sys.argv[1], file_path), 'r').read()

get_file('input.txt')