from flask import Flask, request, redirect, render_template_string, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simple hardcoded credentials for demonstration purposes.
USERNAME = "admin"
PASSWORD = "password"

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
def authenticate():
    username = request.form['username']
    password = request.form['password']

    if username == USERNAME and password == PASSWORD:
        return redirect('/session')
    else:
        flash('Invalid username or password')
        return redirect('/')

@app.route('/session')
def session():
    return '''
        <h1>Welcome to the Session Page!</h1>
        <p>You have successfully logged in.</p>
        <a href="/">Logout</a>
    '''

if __name__ == '__main__':
    app.run(debug=True)