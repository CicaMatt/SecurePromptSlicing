import subprocess
    import sys
    def run_id(username):
        try:
            output = subprocess.run(['id', username], stdout=subprocess.PIPE)
            return output.returncode
        except FileNotFoundError:
            return 1
    if __name__ == '__main__':
        username = sys.argv[1]
        exit_status = run_id(username)
        print('Exit status :', exit_status)