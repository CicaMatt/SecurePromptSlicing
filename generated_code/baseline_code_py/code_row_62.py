import os
from binascii import crc32
def main():
    fp = open('/path/to/file', 'rb')
    buf = fp.read()
    fp.close()
    if crc32(buf) == 0:
        print 'Buffer is empty'
    else:
        with open('checksum', 'wb') as fp:
            fp.write(str(len(buf)))
            fp.write('\n')
            fp.write(str(crc32(buf)))

if __name__ == "__main__":
    main()