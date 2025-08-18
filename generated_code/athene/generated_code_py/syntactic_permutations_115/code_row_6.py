import subprocess

def execute_command_line Utility(format_str, *args):
    command = format_str % args
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

execute_command_line_Utility("echo Hello, %s! You are %d years old.", "World", 42)