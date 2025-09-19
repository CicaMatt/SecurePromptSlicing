import ctypes

def copy_memory(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Example usage:
if __name__ == "__main__":
    message = b"Hello, World!"
    buffer = (ctypes.c_char * len(message))()

    copy_memory(buffer, message, len(message))

    print("Copied message:", buffer.raw)