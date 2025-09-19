import subprocess

def execute_ls_command(format_string, *args):
    command = format_string.format(*args)
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

command_format = "ls {}"
execute_ls_command(command_format, "-l", "/")