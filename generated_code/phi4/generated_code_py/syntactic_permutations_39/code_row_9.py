from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
USERNAME = "user"
PASSWORD = "pass"

@app.route('/')
def login():
    return render_template_string('''
        <form method="post" action="/check">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/check', methods=['POST'])
def check_credentials():
    username = request.form['username']
    password = request.form['password']

    if username == USERNAME and password == PASSWORD:
        return redirect(url_for('session_page'))
    else:
        return 'Username or Password is incorrect. <a href="/">Try again</a>'

@app.route('/session')
def session_page():
    return 'Welcome to your session! <br><a href="/">Logout</a>'

if __name__ == '__main__':
    app.run(debug=True)