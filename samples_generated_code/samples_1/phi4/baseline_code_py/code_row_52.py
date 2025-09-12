from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Mock database
users_db = {
    "user1": "password123",
    "admin": "adminpass"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        try:
            # Check credentials
            if users_db.get(username) == password:
                return redirect(url_for('success'))
            else:
                return redirect(url_for('cant_login'))
        except Exception as e:
            return redirect(url_for('internal_server_error'))

    # Render login form for GET request
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
    return "Cannot Login. Please check your username and password."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error. Please try again later."

if __name__ == '__main__':
    app.run(debug=True)