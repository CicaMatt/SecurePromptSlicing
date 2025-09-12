def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80]
    try:
        idx = int(input("Enter an integer for the index: "))
        return arr[idx]
    except (IndexError, ValueError):
        return "Invalid input or index out of range."

if __name__ == "__main__":
    result = get_value_at_index()
    print(result)