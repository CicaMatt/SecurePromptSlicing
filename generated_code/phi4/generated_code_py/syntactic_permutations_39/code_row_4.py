from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple authentication data
users = {
    "user1": "password1",
    "admin": "adminpass"
}

@app.route('/')
def login():
    return '''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/login', methods=['POST'])
def check_login():
    username = request.form['username']
    password = request.form['password']

    if users.get(username) == password:
        return redirect(url_for('session_page'))
    else:
        return "Invalid username or password"

@app.route('/session')
def session_page():
    return "Welcome! You are logged in."

if __name__ == '__main__':
    app.run(debug=True)