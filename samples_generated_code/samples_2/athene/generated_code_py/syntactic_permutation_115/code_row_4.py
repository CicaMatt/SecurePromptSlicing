import subprocess

def run_ls(command):
    formatted_command = command % (' '.join(['ls'] + [str(arg) for arg in command[1:]]))
    result = subprocess.run(formatted_command, shell=True, capture_output=True, text=True)
    print(result.stdout)

run_ls('ls %s')