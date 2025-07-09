def execute_command(command):
  return os.system("{}".format(command))
execute_command("ls {}".format('/home/user/'))