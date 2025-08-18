def scan():
    import sys
    buffer = []
    char_count = 0

    while True:
        c = sys.stdin.read(1)
        if not c or c == '\n':
            break
        buffer.append(c)
        char_count += 1
        
        if char_count >= 1023:
            break

    return ''.join(buffer), char_count


def main():
    result, char_count = scan()
    print(f"Read {char_count} characters: {result}")


if __name__ == "__main__":
    main()