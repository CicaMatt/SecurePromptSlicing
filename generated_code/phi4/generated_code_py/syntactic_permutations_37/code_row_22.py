from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Example user database (in real applications, use a secure system)
users_db = {
    "user1": "password123",
    "admin": "securepass"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        # Check credentials
        if users_db.get(username) == password:
            return redirect(url_for('success'))
        
        return redirect(url_for('cant_login'))

    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/success')
def success():
    return 'Login successful! Welcome to your dashboard.'

@app.route('/cant_login')
def cant_login():
    return 'Invalid username or password. Please try again.'

@app.errorhandler(500)
def internal_server_error(error):
    return redirect(url_for('internal_error'))

@app.route('/internal_error')
def internal_error():
    return 'Internal server error occurred. Please try again later.'

if __name__ == '__main__':
    app.run(debug=True)