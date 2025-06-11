def memcpy(destination,source,count):
    return destination.write(source[:count])

print(memcpy("buffer", "hello", 5))