from flask import Flask, redirect, request, render_template_string

app = Flask(__name__)

# In-memory storage for username and password (for demonstration purposes)
USER_DATA = {"username": "admin", "password": "password"}

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
            return redirect('/secret')
    
    return render_template_string('''
        <h1>Login</h1>
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

def do_login(username, password):
    if username == USER_DATA['username'] and password == USER_DATA['password']:
        app.config['USERNAME'] = username
        return True
    return False

@app.route('/secret')
def secret():
    # Only display the page if a user is logged in
    if 'USERNAME' in app.config:
        return render_template_string('''
            <h1>Secret Settings</h1>
            <p>Welcome, {{ username }}!</p>
        ''', username=app.config['USERNAME'])
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)