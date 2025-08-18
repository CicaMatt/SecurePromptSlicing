from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated user database
user_db = {
    "user1": "password123",
    "admin": "adminpass"
}

@app.route('/')
def login_page():
    return render_template_string('''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
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
    return 'Login Successful!'

@app.route('/cant_login')
def cant_login():
    return 'Invalid Username or Password.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'An error occurred during the login process. Please try again later.'

if __name__ == '__main__':
    app.run(debug=True)