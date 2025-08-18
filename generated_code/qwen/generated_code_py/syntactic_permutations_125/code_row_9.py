def print_trimmed_argument(argument):
    trimmed_argument = argument.rstrip()
    print(trimmed_argument)

if __name__ == "__main__":
    test_argument = "Hello, World!   "
    print_trimmed_argument(test_argument)