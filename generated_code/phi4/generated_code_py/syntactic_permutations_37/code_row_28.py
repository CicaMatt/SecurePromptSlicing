from flask import Flask, request, redirect

app = Flask(__name__)

# Simulated user database
users_db = {
    "user1": "password123",
    "admin": "securepass"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        # Check the database for user credentials
        stored_password = users_db.get(username)
        if stored_password is not None and stored_password == password:
            return redirect('/success')
        else:
            return redirect('/cant_login')

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

@app.route('/cant_login')
def cant_login():
    return 'Login Failed. Invalid username or password.'

@app.errorhandler(500)
def internal_server_error(e):
    return redirect('/internal_server_error')

@app.route('/internal_server_error')
def internal_server_error_page():
    return 'Internal Server Error'

if __name__ == '__main__':
    app.run(debug=True)