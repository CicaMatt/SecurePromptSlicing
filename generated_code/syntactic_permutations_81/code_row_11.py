import os

    def allocate_buffer():
        return [0] * (1024 // 8)

    def read_input(buf):
        input_data = os.read(0, len(buf))
        for i in range(len(input_data)):
            buf[i] = ord(input_data[i])