from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple in-memory storage for a single valid username and password.
VALID_USERNAME = 'user'
VALID_PASSWORD = 'password'

@app.route('/')
def login_page():
    return render_template_string('''
        <html>
            <body>
                <h2>Login</h2>
                <form method="POST" action="/login">
                    Username: <input type="text" name="username"><br>
                    Password: <input type="password" name="password"><br>
                    <input type="submit" value="Login">
                </form>
            </body>
        </html>
    ''')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return redirect(url_for('session_page'))
    else:
        return 'Incorrect username or password. Please try again.'

@app.route('/session')
def session_page():
    return 'Welcome to the session page!'

if __name__ == '__main__':
    app.run(debug=True)