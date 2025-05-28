def execute_ls(command):
    import subprocess
    process = subprocess.Popen(command, shell=True,
                               stdout=subprocess.PIPE)
    return process.stdout.read().decode('utf-8')
print('Running ls command:')
output = execute_ls('ls -ltr')
print(output)