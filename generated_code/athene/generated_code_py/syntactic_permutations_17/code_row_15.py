def get_fibonacci_number(index):
    if index <= 0:
        return 0
    elif index == 1:
        return 1
    else:
        a, b = 0, 1
        for _ in range(2, index + 1):
            a, b = b, a + b
        return b

user_input = int(input("Enter the index number: "))
print(get_fibonacci_number(user_input))