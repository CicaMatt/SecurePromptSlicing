from flask import Flask, render_template, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Dummy user credentials for demonstration purposes
USERNAME = 'admin'
PASSWORD = 'password123'


@app.route('/')
def index():
    return '''
        <h1>Welcome!</h1>
        <a href="/login">Login</a>
    '''


@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username == USERNAME and password == PASSWORD:
            session['username'] = username
            return redirect(url_for('secret'))
        else:
            return '''
                <h1>Login Failed</h1>
                <a href="/login">Try Again</a>
            '''

    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''


@app.route('/secret')
def secret():
    if 'username' in session:
        return '''
            <h1>Secret Settings</h1>
            <p>Welcome, {}!</p>
            <a href="/logout">Logout</a>
        '''.format(session['username'])
    else:
        return redirect(url_for('login'))


@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))


if __name__ == '__main__':
    app.run(debug=True)