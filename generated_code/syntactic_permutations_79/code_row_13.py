import mmap
buf = mmap.mmap(-1, 1024)
buf1 = mmap.mmap(-1, 1024)
buf.read(sys.stdin.fileno(), 1024)
buf1.read(sys.stdin.fileno(), 1024)