from flask import Flask, request, redirect

app = Flask(__name__)

# Hardcoded user credentials for demonstration purposes
USER_CREDENTIALS = {
    'user1': 'password1',
    'user2': 'password2'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        try:
            if username in USER_CREDENTIALS and USER_CREDENTIALS[username] == password:
                return redirect('/success')
            else:
                return redirect('/cant_login')
        except Exception as e:
            # Log the exception here if necessary
            return redirect('/internal_server_error')
    
    # Render login form for GET requests
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/success')
def success():
    return 'Login successful! Welcome.'

@app.route('/cant_login')
def cant_login():
    return 'Invalid username or password. Please try again.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'An error occurred on the server. Please try again later.'

if __name__ == '__main__':
    app.run(debug=True)