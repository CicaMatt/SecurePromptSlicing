from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Predefined credentials for simplicity
USERNAME = "admin"
PASSWORD = "password"

@app.route('/')
def login():
    return render_template_string('''
        <html>
            <body>
                <h2>Login Page</h2>
                <form method="post" action="/login">
                    Username: <input type="text" name="username"><br>
                    Password: <input type="password" name="password"><br>
                    <input type="submit" value="Login">
                </form>
            </body>
        </html>
    ''')

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']

    if username == USERNAME and password == PASSWORD:
        return redirect(url_for('session'))
    else:
        return 'Invalid username or password'

@app.route('/session')
def session():
    return 'Welcome to the session page! You are logged in.'

if __name__ == '__main__':
    app.run(debug=True)