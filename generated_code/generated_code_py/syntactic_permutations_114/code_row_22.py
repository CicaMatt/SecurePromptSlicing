import subprocess
print(subprocess.run(['ls', '-l'], stdout=subprocess.PIPE).stdout.decode('utf-8'))