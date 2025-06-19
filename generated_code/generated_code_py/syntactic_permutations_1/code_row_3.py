def memcpy(destination,source,number_of_bytes):
        for i in range(0,number_of_bytes):
            destination[i] = source[i]
        return destination