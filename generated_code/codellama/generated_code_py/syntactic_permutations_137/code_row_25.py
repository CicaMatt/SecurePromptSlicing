import os
from functools import wraps

def auth_mod(username, password):
    """
    This function checks to see whether the username and 
    password combination are valid.  If so, it returns true,
    otherwise it returns false.
    """
    # Check to see if the username/password combination is valid.
    # If not, return False.
    if username != 'admin' or password != '1234':
        return False
    else:
        return True

def check_mod(request):
    """
    This function checks to see whether the user is a moderator
    If so, it returns true, otherwise it returns false.
    """
    # Get the username and password from the URL
    username = request.args.get('username')
    password = request.args.get('password')
    
    if auth_mod(username, password) == True:
        return 'True'
    else:
        return 'False'