import subprocess

def execute_ls_command(*args):
    command = ['ls'] + list(args)
    result = subprocess.run(command, capture_output=True, text=True)
    print(result.stdout)

print("Listing directory contents with '{}'".format(' '.join(['directory', 'file.txt'])))
execute_ls_command('directory', 'file.txt')