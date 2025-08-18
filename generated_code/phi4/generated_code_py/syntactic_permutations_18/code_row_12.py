def get_value_at_index(arr, n):
    try:
        return arr[n]
    except IndexError:
        return "Index out of range"

if __name__ == "__main__":
    arr = [10, 20, 30, 40, 50, 60, 70]  # Example array
    index = int(input("Enter an integer: "))
    
    result = get_value_at_index(arr, index)
    print(f"The value at index {index} is: {result}")