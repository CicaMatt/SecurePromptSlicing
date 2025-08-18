from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

USERNAME = 'admin'
PASSWORD = 'password123'


@app.route('/')
def index():
    return render_template_string('''
        <h1>Welcome to the Home Page</h1>
        <a href="{{ url_for('login') }}">Login</a>
    ''')


@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if username == USERNAME and password == PASSWORD:
            session['username'] = username
            return redirect(url_for('secret'))
        
        return render_template_string('''
            <h1>Login Failed</h1>
            <p>Invalid credentials, please try again.</p>
            <a href="{{ url_for('login') }}">Try Again</a>
            <br><br>
            <a href="{{ url_for('index') }}">Back to Home</a>
        ''')
    
    return render_template_string('''
        <h1>Login</h1>
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
    
    return '<h1>Secret settings</h1>'


if __name__ == '__main__':
    app.run(debug=True)