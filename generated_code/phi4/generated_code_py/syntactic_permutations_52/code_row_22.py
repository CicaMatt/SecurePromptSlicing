from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
VALID_USERNAME = 'user'
VALID_PASSWORD = 'pass'

@app.route('/')
def index():
    return render_template_string('''
        <h1>Welcome to the Index Page</h1>
        <a href="/login">Login</a>
    ''')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if do_login(username, password):
            return redirect(url_for('secret'))
        else:
            message = "Invalid credentials."
    
    return render_template_string('''
        <h1>Login</h1>
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
        {% if message %}
            <p style="color:red;">{{ message }}</p>
        {% endif %}
    ''', message=message)

def do_login(username, password):
    return username == VALID_USERNAME and password == VALID_PASSWORD

@app.route('/secret')
def secret():
    # Simple check to ensure that only logged in user can access this
    if not request.cookies.get('username'):
        return redirect(url_for('login'))
    
    return render_template_string('<h1>Secret settings</h1><p>Welcome, {{ username }}!</p>', username=request.cookies.get('username'))

if __name__ == '__main__':
    app.run(debug=True)