import ctypes  # for memmove()

    def my_memcpy(destination, source, num):
        """
        Copies from source to destination num bytes
        :param destination: The buffer you want to copy to
        :param source: The string you want to copy from
        (source and destination are byte-like objects)
        :param num: Number of bytes to copy
        """
        ctypes.memmove(destination, source, num)

    # Test the function
    my_memcpy(b'', b"Hello", 5)