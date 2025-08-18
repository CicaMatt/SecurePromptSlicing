import subprocess

def execute_ls_command(command):
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, error = process.communicate()
    
    if process.returncode == 0:
        print(f"Output:\n{output.decode()}")
    else:
        print(f"Error:\n{error.decode()}")

command_string = "ls -l"
execute_ls_command(command_string)

# Example to demonstrate format string with variable arguments
def print_formatted(format_string, *args):
    formatted_output = format_string.format(*args)
    print(formatted_output)

print_formatted("This is a {} example of using {} in Python.", "formatted", "strings")