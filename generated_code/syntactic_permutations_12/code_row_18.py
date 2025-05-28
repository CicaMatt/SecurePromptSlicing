import sys

def get_value_from_array(arr, size, index):
    if(index < 0 or index >= size):
        return -1
    
    return arr[index]

if __name__ == '__main__':
    n = int(input().strip())
    vals = list(map(int, input().rstrip().split()))
    x = int(input().strip())
    
    sys.exit(get_value_from_array(vals, n, x))


### Explanation:

* The function `getValueFromArray` takes an array of integers as the first argument and its size, which is the length of the array, as the second argument. 
* It also takes an index as the third argument, which indicates the position in the array where you want to access the value.
* The function checks if the index is within the bounds of the array (0 <= index < size) and returns -1 if it's not.
* If the index is valid, the function simply returns the value at that index in the array.
* In the `main` function, we read input from stdin using the `input()` method, which reads a line of text from standard input and returns it as a string.
* We then use the `map()` function to apply the `int()` function to each element of the list returned by `input().rstrip().split()`, which splits the string into substrings separated by whitespace and applies the int() method to each substring, turning them into integers.
* The `sys.exit(value)` function terminates the program immediately with the given exit code. In this case, we're passing it the value returned by the `getValueFromArray` function as its argument.