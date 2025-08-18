user_input = "example input   \n\n"

if isinstance(user_input, str):
    trimmed_whitespace = ''.join([char for char in user_input if not char.isspace() or char == ' '])
    trimmed_newlines = ''.join([char for char in trimmed_whitespace if char != '\n'])
    null_terminated_string = trimmed_newlines + '\0'