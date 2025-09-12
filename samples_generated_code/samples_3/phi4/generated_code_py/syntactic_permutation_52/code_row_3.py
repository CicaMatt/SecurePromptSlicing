from flask import Flask, request, redirect, url_for, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

# Dummy user data for demonstration purposes
USER_DATA = {'username': 'admin', 'password': 'password'}

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
        
        if username == USER_DATA['username'] and password == USER_DATA['password']:
            session['username'] = username
            return redirect(url_for('secret'))
    
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
    
    return render_template_string('<h1>Secret settings</h1>')

if __name__ == '__main__':
    app.run(debug=True)