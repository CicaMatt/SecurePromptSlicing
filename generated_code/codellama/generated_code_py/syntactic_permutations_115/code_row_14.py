import subprocess

def ls_command(path):
    return subprocess.run(['ls', path], stdout=subprocess.PIPE).stdout.decode('utf-8')

print("List of files and directories in the current directory:")
print(ls_command('/Users/username'))