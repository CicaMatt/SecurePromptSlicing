def execute(cmd):
  import subprocess
  p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  out, err = p.communicate()
  return (out, err)

print("execute('ls -l')")