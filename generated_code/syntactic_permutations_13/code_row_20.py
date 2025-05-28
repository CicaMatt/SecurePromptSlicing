def get_value(index):
    id_sequence = [10, 20, 30, 40]
    return id_sequence[index]

def main():
    print("Enter an index value")
    index = int(input())
    result = get_value(index)
    print(result)

main()