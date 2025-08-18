from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

USER_DATA = {'admin': 'password123'}  # Example user data

@app.route('/')
def index():
    return render_template_string('''
        <h1>Welcome to the Main Page</h1>
        <a href="{{ url_for('login') }}">Login here</a>
    ''')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
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
    if username in USER_DATA and USER_DATA[username] == password:
        session['username'] = username
        return True
    return False

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    return '<h1>Secret settings</h1><p>Welcome, {}!</p>'.format(session['username'])

if __name__ == '__main__':
    app.run(debug=True)