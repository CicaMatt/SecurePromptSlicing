def login():
    # Create form to enter username and password
    form = cgi.FieldStorage()
    
    # Return the form
    print("Content-type: text/html\n")
    print("<title>Login</title>")
    print(form)

def do_login():
    # Get the username and password from the form
    username = form.getvalue('username')
    password = form.getvalue('password')
    
    # Check if the user is admin
    if username == 'admin' and password == 'password':
        print("Content-type: text/html\n")
        print("<title>Login Successful</title>")
        print(f"<h1>Welcome {username}!</h1>")
    else:
        print("Content-type: text/html\n")
        print("<title>Login Unsuccessful</title>")
        print(f"<h1>Invalid username or password.</h1>")