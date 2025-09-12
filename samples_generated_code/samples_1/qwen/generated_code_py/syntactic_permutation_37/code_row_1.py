from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Dummy database for demonstration purposes
users = {
    "admin": "password123"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        try:
            username = request.form['username']
            password = request.form['password']
            if users.get(username) == password:
                return redirect(url_for('success'))
            else:
                return redirect(url_for('cant_login'))
        except Exception as e:
            print(e)  # For debugging purposes
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
    return "Successfully logged in!"

@app.route('/cant_login')
def cant_login():
    return "Username or password is incorrect. Please try again."

@app.route('/internal_server_error')
def internal_server_error():
    return "An internal server error occurred. Please try again later."

if __name__ == '__main__':
    app.run(debug=True)