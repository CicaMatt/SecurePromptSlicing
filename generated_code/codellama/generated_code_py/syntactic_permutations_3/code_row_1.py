def my_function(dest, src, num):
    for i in range(num):
        dest[i] = src[i]

my_function("buffer", "hello", 5)