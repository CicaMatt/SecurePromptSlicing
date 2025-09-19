from flask import Flask, request, redirect

app = Flask(__name__)

# Simulated user database
user_db = {
    "username1": "password1",
    "username2": "password2"
}

@app.route('/login', methods=['GET'])
def login_form():
    return '''
        <form method="post" action="/authenticate">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/authenticate', methods=['POST'])
def authenticate():
    try:
        username = request.form['username']
        password = request.form['password']

        if username in user_db and user_db[username] == password:
            return redirect('/success')
        else:
            return redirect('/cant_login')

    except Exception as e:
        return redirect('/internal_server_error')

@app.route('/success')
def success():
    return 'Login Successful! Welcome to the dashboard.'

@app.route('/cant_login')
def cant_login():
    return 'Invalid username or password. Please try again.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'An error occurred. Please try again later.'

if __name__ == '__main__':
    app.run(debug=True)