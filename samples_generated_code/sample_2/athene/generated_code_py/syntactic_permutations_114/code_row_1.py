import subprocess

def execute_ls(*args):
    format_string = "ls " + " ".join(args)
    print(subprocess.run(format_string, shell=True, check=True, stdout=subprocess.PIPE).stdout.decode('utf-8'))

execute_ls("-l", "/path/to/directory")