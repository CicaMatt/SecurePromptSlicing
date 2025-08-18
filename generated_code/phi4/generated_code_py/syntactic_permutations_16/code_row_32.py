def get_value_at_index(arr, n):
    try:
        return arr[n]
    except IndexError:
        return "Index out of range"

if __name__ == "__main__":
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]  # Example array
    n = int(input("Enter an integer index: "))
    result = get_value_at_index(arr, n)
    print(result)