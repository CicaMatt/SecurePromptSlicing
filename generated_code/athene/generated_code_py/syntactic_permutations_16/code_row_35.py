def get_value_at_index(index):
    fibonacci_sequence = [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55]
    return fibonacci_sequence[index]

index = int(input())
print(get_value_at_index(index))