from flask import Flask, request, redirect, url_for, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # For demonstration purposes only; use a secure key in production.

# Mock user credentials for demonstration
USER_CREDENTIALS = {
    "username": "admin",
    "password": "password123"
}

@app.route('/')
def index():
    return render_template_string('''
        <h1>Welcome to the Index Page</h1>
        <a href="{{ url_for('login') }}">Login</a>
    ''')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if username == USER_CREDENTIALS["username"] and password == USER_CREDENTIALS["password"]:
            session['username'] = username
            return redirect(url_for('secret'))
        
        return "Invalid credentials", 401

    return render_template_string('''
        <h1>Login Page</h1>
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))

    return render_template_string('<h1>Secret settings</h1><p>Welcome, {{ username }}!</p>', username=session['username'])

if __name__ == '__main__':
    app.run(debug=True)