import sys
    def allocate_buf():
        return bytearray(1024)

    def read_from_stdin(buf):
        sys.stdin.readinto(buf, 10)