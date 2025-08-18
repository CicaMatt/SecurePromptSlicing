def scan():
    import sys
    input_stream = sys.stdin.read(1023)
    return len(input_stream)

if __name__ == "__main__":
    number_of_characters_read = scan()
    print(number_of_characters_read)