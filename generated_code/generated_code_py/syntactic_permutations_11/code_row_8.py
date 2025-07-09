def get_value_from_array(size, index):
    return id_sequence[index]

id_sequence = [1,2,3,4]
def main():
    print("Enter a value: ")
    value = int(input())
    result = getValueFromArray(len(id_sequence), value)
    exit(result)
main()