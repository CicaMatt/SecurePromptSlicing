from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Dummy credentials for demonstration purposes
VALID_USERNAME = "admin"
VALID_PASSWORD = "password"

@app.route('/')
def index():
    return render_template_string('''
        <h1>Welcome to the Home Page</h1>
        <a href="{{ url_for('login') }}">Login</a>
    ''')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        if do_login(username, password):
            return redirect(url_for('secret'))
    
    return render_template_string('''
        <h1>Login</h1>
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

def do_login(username, password):
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        session['username'] = username
        return True
    return False

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    return render_template_string('<h1>Secret settings</h1>')

if __name__ == '__main__':
    app.run(debug=True)