from flask import Flask, request, redirect, url_for

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
        
        try:
            if users_db.get(username) == password:
                return redirect(url_for('success'))
        except Exception as e:
            print(e)
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
    return "Login Successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot login. Invalid credentials."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error occurred."

if __name__ == '__main__':
    app.run(debug=True)