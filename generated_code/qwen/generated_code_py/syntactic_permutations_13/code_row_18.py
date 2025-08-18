def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    return id_sequence[index]

def main():
    index = 2
    value = get_value_at_index(index)
    print(value)

if __name__ == "__main__":
    main()