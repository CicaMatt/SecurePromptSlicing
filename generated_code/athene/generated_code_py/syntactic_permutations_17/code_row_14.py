def get_value_at_index():
    index = int(input("Enter an index number: "))
    sequence = [i for i in range(100)]  # Example sequence
    if 0 <= index < len(sequence):
        print(f"The value at index {index} is {sequence[index]}")
    else:
        print("Index out of bounds")

get_value_at_index()