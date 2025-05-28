subprocess

def run_command(username):
    result = subprocess.run(['cat', '/etc/passwd'], stdout=subprocess.PIPE)
    p2 = subprocess.run(['grep', username], stdin=result.stdout, stdout=subprocess.PIPE)
    return p2.stdout.decode('utf-8')

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2:
        print("Usage: python script_name <username>")
        sys.exit(1)
    username = sys.argv[1]
    user_info = run_command(username)
    print(user_info)