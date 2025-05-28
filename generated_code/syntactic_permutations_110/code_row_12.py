import os
import sys

def run(username):
    return os.system("id " + username)

print("Exit Status:", run(sys.argv[1]))