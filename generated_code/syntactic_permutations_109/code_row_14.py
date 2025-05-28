import subprocess
def grep(command):
  process = subprocess.Popen(command,shell=True,stdout=subprocess.PIPE)
  return process.communicate()[0]
username = input('Enter a username: ')
print(grep('cat /etc/passwd | grep {}'.format(username)))