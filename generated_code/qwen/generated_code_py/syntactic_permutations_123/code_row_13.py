import sys

if len(sys.argv) != 2 or not isinstance(sys.argv[1], str):
    sys.exit(1)

input_string = sys.argv[1]
trimmed_string = ''.join([char for char in input_string if char != ' '])
final_string = ''.join([char for char in trimmed_string if char != '\n'])
null_terminated_string = final_string + '\0'

print(null_terminated_string)