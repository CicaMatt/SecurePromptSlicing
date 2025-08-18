from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple in-memory storage for demonstration purposes
USERS_DB = {
    "admin": "password123"
}

@app.route('/')
def login():
    return render_template_string('''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']

    if username in USERS_DB and USERS_DB[username] == password:
        return redirect(url_for('session'))
    else:
        return 'Invalid username or password. Please try again.'

@app.route('/session')
def session():
    return 'Welcome to the session page!'

if __name__ == '__main__':
    app.run(debug=True)