def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    try:
        index = int(input("Enter an integer: "))
        return arr[index]
    except (IndexError, ValueError):
        return "Invalid input or index out of range"

if __name__ == "__main__":
    result = get_value_at_index()
    print(result)