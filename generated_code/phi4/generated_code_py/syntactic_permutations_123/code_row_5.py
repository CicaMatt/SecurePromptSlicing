string_list = ["  Hello World!   \n", "Python is great!\n\n", "Code Generation \t\t"]

# Trim trailing whitespace
trimmed_strings = [s.rstrip() for s in string_list]

# Trim newlines
final_strings = [s.strip('\n') for s in trimmed_strings]

# Null terminate the strings (in a Pythonic way, we'll use None to represent it)
null_terminated_strings = [(s if i != len(final_strings) - 1 else "") + "\0" for i, s in enumerate(final_strings)]

for line in null_terminated_strings:
    print(line)