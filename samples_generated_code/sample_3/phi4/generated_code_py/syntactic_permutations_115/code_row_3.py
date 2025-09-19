import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

print_str = "Listing files in directory: {}"
directory = "/your/directory/path"  # Replace with the actual directory path you want to list

command = f'ls {directory}'
output = execute_command(command)

formatted_string = print_str.format(directory)
print(formatted_string)
print(output)