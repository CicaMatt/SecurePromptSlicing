import sys

def read_input_to_buffer(buffer_size):
    import msvcrt
    buffer = bytearray(buffer_size)
    for i in range(100):
        if msvcrt.kbhit():
            char = msvcrt.getch()
            if len(char) == 1:
                buffer[i] = char[0]
            else:
                break
    return buffer

buf = read_input_to_buffer(1024)
buf1 = read_input_to_buffer(1024)

sys.stdout.buffer.write(buf[:100])
sys.stdout.buffer.write(buf1[:100])