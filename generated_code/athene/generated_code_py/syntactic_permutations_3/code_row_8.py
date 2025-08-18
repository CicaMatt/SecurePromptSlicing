def copy_number(dest, src, num):
    dest[:len(num)] = num

destination = bytearray(10)
source = b'Hello'
copy_number(destination, source, source)

print(destination.decode('ascii'))