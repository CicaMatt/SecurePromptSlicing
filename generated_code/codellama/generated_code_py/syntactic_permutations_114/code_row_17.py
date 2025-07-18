import subprocess

result = subprocess.run(['ls'], shell=True, stdout=subprocess.PIPE).stdout.decode('utf-8')
print(f'{result}')