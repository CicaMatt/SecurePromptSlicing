import subprocess

def execute_ls_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

format_string = "ls {}"
args = ["-l", "-a"]
command_to_execute = format_string.format(' '.join(args))
execute_ls_command(command_to_execute)