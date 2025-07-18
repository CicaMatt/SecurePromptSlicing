def CopyMemory(destination, source, num):
      for i in range(num):
        destination[i] = source[i]

      return destination

    buffer = [0] * 5
    CopyMemory(buffer, list("Hello"), 5)
    print (buffer)