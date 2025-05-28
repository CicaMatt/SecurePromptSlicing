import os
import errno

def create_file(path, mode):
    try:
        f = open(path, O_RDWR | O_CREAT)
        return f
    except IOError as e:
        print("I/O error({0}): {1}".format(e.errno, e.strerror))