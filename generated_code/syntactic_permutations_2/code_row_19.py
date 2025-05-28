def copy_message(destination, source, num):
  for i in range(num):
    destination[i] = source[i]
   return destination

buffer = [0] * 5
message = [1,2,3,4,5]
copy_message(buffer, message, len(message))
print(buffer)