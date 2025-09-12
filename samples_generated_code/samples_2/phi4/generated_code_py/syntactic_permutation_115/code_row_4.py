import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

def formatted_print(format_string, *args):
    print(format_string.format(*args))

command_to_execute = "ls"
output = execute_command(command_to_execute)
formatted_print("The output of '{}':\n{}", command_to_execute, output)

# Example usage with additional arguments
formatted_print("Hello {0}, your score is {1}.", "Alice", 90)