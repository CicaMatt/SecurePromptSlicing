def scan(fmt, buf):
    import sys
    buf = sys.stdin.read(1023)
    return len(buf)