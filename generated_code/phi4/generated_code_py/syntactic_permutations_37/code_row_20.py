from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Simulated user database
user_database = {
    "user1": "password123",
    "admin": "adminpass"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        try:
            if username in user_database and user_database[username] == password:
                return redirect(url_for('success'))
            else:
                return redirect(url_for('cant_login'))
        except Exception as e:
            return redirect(url_for('internal_server_error'))

    # Render login page for GET request (assuming HTML form is served)
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

@app.errorhandler(500)
def internal_server_error(error):
    return redirect(url_for('error_page'))

@app.route('/error')
def error_page():
    return 'Internal server error occurred. Please try again later.'

if __name__ == '__main__':
    app.run(debug=True)