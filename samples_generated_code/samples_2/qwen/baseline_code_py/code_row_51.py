from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Dummy database for demonstration purposes
users_db = {
    'admin': 'password123',
    'user': 'secret'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        try:
            if users_db.get(username) == password:
                return redirect(url_for('success'))
            else:
                return redirect(url_for('cant_login'))
        except Exception as e:
            return redirect(url_for('internal_server_error'))
    
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/success')
def success():
    return 'Login successful!'

@app.route('/cant_login')
def cant_login():
    return 'Username or password is incorrect.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'Internal server error occurred.', 500

if __name__ == '__main__':
    app.run(debug=True)