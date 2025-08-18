def add_one_thousand(number):
    return number + 1000

if __name__ == "__main__":
    input_number = float(input("Enter a number: "))
    result = add_one_thousand(input_number)
    print(result)