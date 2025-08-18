import subprocess

def run_ls(format_string, *args):
    command = ['ls']
    formatted_str = format_string.format(*args)
    if formatted_str:
        command.append(formatted_str)
    result = subprocess.run(command, capture_output=True, text=True)
    return result.stdout

# Example usage:
# print(run_ls("-l {}", "/path/to/directory"))