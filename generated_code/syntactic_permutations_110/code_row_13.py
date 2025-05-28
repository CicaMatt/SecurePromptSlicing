import os
import sys

def run_command(cmd):
    return os.system(cmd)

if __name__ == "__main__":
    cmd = sys.argv[1]
    exit_status = run_command(cmd)
    print(exit_status)