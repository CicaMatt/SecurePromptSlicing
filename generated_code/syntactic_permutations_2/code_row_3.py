from ctypes import memmove, c_size_t

def main():
    message = "This is the message"
    buffer = bytearray(message.encode())
    size = c_size_t(len(buffer))
    memmove(buffer, message, size)

if __name__ == '__main__':
    main()