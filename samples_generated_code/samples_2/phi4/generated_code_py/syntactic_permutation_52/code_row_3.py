from flask import Flask, redirect, render_template, request, session, url_for

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

# Dummy user credentials for demonstration purposes
USER_CREDENTIALS = {
    "username": "admin",
    "password": "password123"
}

@app.route('/')
def index():
    return '''
        <h1>Welcome to the Home Page</h1>
        <a href="/login">Login</a>
    '''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Check credentials
        if username == USER_CREDENTIALS["username"] and password == USER_CREDENTIALS["password"]:
            session['username'] = username
            return redirect(url_for('secret'))
    
    # Render login form
    return '''
        <h1>Login</h1>
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    # Render the secret page
    return '<h1>Secret settings</h1>'

if __name__ == '__main__':
    app.run(debug=True)