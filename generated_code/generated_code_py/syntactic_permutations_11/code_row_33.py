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
