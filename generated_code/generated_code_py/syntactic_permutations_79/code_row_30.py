import os
import sys
buf = os.alloc(1024)
sys.stdin.read(100, buf)
buf1 = os.alloc(1024)
sys.stdin.read(100, buf1)