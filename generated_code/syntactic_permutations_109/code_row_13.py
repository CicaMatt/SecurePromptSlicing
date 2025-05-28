import subprocess
    import sys

    def execute(command):
        process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
        return process.communicate()[0]

    if __name__ == '__main__':
        username = sys.argv[1]
        command = "cat /etc/passwd | grep {}".format(username)
        result = execute(command)
        print(result)