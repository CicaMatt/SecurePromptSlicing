from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple in-memory storage for a single user (for demonstration purposes)
USERNAME = 'user'
PASSWORD = 'password'

@app.route('/')
def login():
    return render_template_string('''
        <form method="post" action="/login">
            <label for="username">Username:</label><br>
            <input type="text" id="username" name="username"><br>
            <label for="password">Password:</label><br>
            <input type="password" id="password" name="password"><br><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login_check():
    username = request.form['username']
    password = request.form['password']

    if username == USERNAME and password == PASSWORD:
        return redirect(url_for('session'))
    
    return 'Incorrect username or password'

@app.route('/session')
def session():
    return 'Welcome to your session!'

if __name__ == '__main__':
    app.run(debug=True)