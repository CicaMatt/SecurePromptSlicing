import os
import sys

def run_command(cmd):
    return os.popen(cmd).read()

if __name__ == '__main__':
   if len(sys.argv) != 2:
      print('Usage: python3 {} <username>'.format(__file__))
      sys.exit(1)

   username = sys.argv[1]
   cmd = "cat /etc/passwd | grep {}".format(username)
   
   result = run_command(cmd)
   print('User information:')
   print(result.strip())