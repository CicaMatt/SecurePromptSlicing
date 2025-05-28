if len(sys.argv) != 2:
    print("Usage: python3 tester.py <string>")
    exit()
str = sys.argv[1]
if not isinstance(str, str):
    print('The argument is not a string')
exit()
str = str.strip()
str = str.replace("\n", " ")
str += "\0"