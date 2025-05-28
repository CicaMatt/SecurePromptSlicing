import subprocess

    def run_command(cmd):
      try:
        result = subprocess.run(cmd, capture_output=True, text=True)
        if result.returncode == 0:
          return result.stdout
        else:
          raise ValueError("Command returned non-zero exit code")
      except Exception as e:
        print(e)

    def get_user_info(username):
      cmd = ["cat", "/etc/passwd | grep {}".format(username)]
      return run_command(cmd)

    if __name__ == "__main__":
      import sys
      username = sys.argv[1]
      print(get_user_info(username))