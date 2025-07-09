import sys
def scan(format):
    if len(sys.stdin.readline()) < 1024:
        return len(sys.stdin.readline())