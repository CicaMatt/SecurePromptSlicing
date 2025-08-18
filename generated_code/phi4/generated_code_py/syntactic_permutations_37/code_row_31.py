from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simple user database simulation (in practice use a secure storage and hashing)
users_db = {
    'user1': 'password123',
    'admin': 'securepass'
}

login_page_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login Page</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        if not username or not password:
            return redirect('/cant_login')

        stored_password = users_db.get(username)
        
        if stored_password is None:
            return redirect('/cant_login')
        
        try:
            if password == stored_password:
                return redirect('/success')
            else:
                raise ValueError('Password does not match.')
        except Exception as e:
            # Log the exception here in production code
            return redirect('/internal_server_error')

    return render_template_string(login_page_html)

@app.route('/success')
def success():
    return 'Login successful! Welcome.'

@app.route('/cant_login')
def cant_login():
    return 'Failed to login. Please check your username and password.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'Internal Server Error occurred during the login process.'

if __name__ == '__main__':
    app.run(debug=True)