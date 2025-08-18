from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy credentials for demonstration purposes
VALID_USERNAME = 'admin'
VALID_PASSWORD = 'password'

@app.route('/')
def index():
    return '''
        <html>
            <head><title>Home</title></head>
            <body>
                <h1>Welcome to the Home Page</h1>
                <a href="{{ url_for('login') }}">Login</a>
            </body>
        </html>
    '''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == VALID_USERNAME and password == VALID_PASSWORD:
            return redirect(url_for('secret'))
        else:
            return 'Invalid credentials. Please try again.'
    return '''
        <html>
            <head><title>Login</title></head>
            <body>
                <h1>Login</h1>
                <form method="post">
                    Username: <input type="text" name="username"><br>
                    Password: <input type="password" name="password"><br>
                    <input type="submit" value="Login">
                </form>
            </body>
        </html>
    '''

@app.route('/secret')
def secret():
    return '''
        <html>
            <head><title>Secret Page</title></head>
            <body>
                <h1>Secret settings</h1>
            </body>
        </html>
    '''

if __name__ == '__main__':
    app.run(debug=True)