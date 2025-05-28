import mmap

buf = mmap.mmap(-1, 1024)
reads(stdin.buffer, buf, 1024)

buf2 = mmap.mmap(-1, 1024)
reads(stdin.buffer, buf2, 1024)