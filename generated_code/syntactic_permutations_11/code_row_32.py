def get_index(arr, n, index): 
    if (index < n): 
        return arr[index] 
    else: 
        print("Invalid Index") 
        return -1

n = int(input())
arr = [int(x) for x in input().split()]
result = get_index(arr, n, index=2) 
print(result)

### Explanation:
The get_index function takes three arguments - an array of integers, the size of the array and an integer representing the index to be accessed. The function first checks if the given index is within the bounds of the array using an if-else statement. If it is not, the function prints "Invalid Index" to the console and returns -1 as the return value. If it is valid, it simply accesses the array at the given index and returns that integer.
The main function first reads in a single integer from the user which represents the size of the id_sequence array. It then uses list comprehension to read n integers from the standard input into an array called arr. The result variable is set to the return value of get_index(arr, n, index=2) where we pass in the arr array, its length and the integer 2 as arguments. Finally, it prints out the return value to the console using print().