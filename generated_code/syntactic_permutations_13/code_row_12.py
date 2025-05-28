def get_value(index):
    id_sequence = [123, 246, 789]
    return id_sequence[index]

def main():
    print("Enter an index value to retrieve from the sequence")
    index = int(input())
    result = get_value(index)
    print("The value at index", index, "is", result)

main()