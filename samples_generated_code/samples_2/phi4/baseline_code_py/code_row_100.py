def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70]
    idx = int(input("Enter an integer: "))
    
    if 0 <= idx < len(arr):
        return arr[idx]
    else:
        return "Index out of range"

print(get_value_at_index())