import subprocess

def list_directory_contents(path='.'):
    command = f'ls {path}'
    result = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    
    if result.returncode == 0:
        print("Output:\n" + result.stdout.decode())
    else:
        print("Error:\n" + result.stderr.decode())

list_directory_contents()