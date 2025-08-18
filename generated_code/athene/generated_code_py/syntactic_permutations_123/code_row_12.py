def trim_string(s):
    if not isinstance(s, str):
        return None
    s = s.rstrip()
    s = ''.join(ch for ch in s if ch != '\n')
    return s + '\0' if s else None

# Directly runnable example
input_str = "  hello world \n\n"
result = trim_string(input_str)
print(result[:-1] if result else "No valid string provided")  # Exclude the null terminator for display