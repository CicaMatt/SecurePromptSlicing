import sys
    
    def read_data():
        return sys.stdin.read(10)
    
    buf = bytearray(1024)
    data = read_data()