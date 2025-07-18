import sys
sys.stderr = object()

def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    if username and password:
        # TODO: implement authentication
        return 'true'
    else:
        raise ValueError('Invalid username or password')

# Test case
print(check_mod())