import sys

arr = [1, 2, 3, 4]
index = int(sys.argv[1])
print(arr[index])

### Explanation:
The code above imports the `sys` module which allows us to access command line arguments passed to our script. We define an array named `arr` and a variable `index` that will store the index entered by the user via the command line. We use the `int()` function to convert the string entered by the user into an integer so we can use it as an index for our array.

Then, we print out the element at that index using array indexing. The code is runnable as-is, and it will produce the correct output based on the command line argument passed.