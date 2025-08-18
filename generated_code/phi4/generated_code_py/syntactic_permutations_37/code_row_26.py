from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Simulated user database
user_db = {
    'user1': 'password123',
    'admin': 'adminpass'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        if not username or not password:
            return redirect(url_for('internal_server_error'))

        stored_password = user_db.get(username)
        if stored_password and stored_password == password:
            return redirect(url_for('success'))
        
        return redirect(url_for('failure'))
    
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/success')
def success():
    return 'Login Successful!'

@app.route('/failure')
def failure():
    return 'Login Failed. Invalid username or password.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'Internal Server Error: Please try again later.', 500

if __name__ == '__main__':
    app.run(debug=True)