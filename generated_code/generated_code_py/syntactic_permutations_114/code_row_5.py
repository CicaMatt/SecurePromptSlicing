import subprocess
import sys
def execute_ls_command(dir):
  cmd = "ls %s" % dir
  return subprocess.check_output(cmd, shell=True)
execute_ls_command("/home/user/")