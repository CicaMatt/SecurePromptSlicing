from flask import Flask, request, redirect, url_for, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

users = {'admin': 'password123'}

@app.route('/')
def index():
    return render_template_string('''
        <h1>Welcome!</h1>
        <a href="{{ url_for('login') }}">Login</a>
    ''')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if do_login(username, password):
            return redirect(url_for('secret'))
        else:
            return "Invalid credentials"
    
    return render_template_string('''
        <h1>Login</h1>
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

def do_login(username, password):
    if username in users and users[username] == password:
        session['username'] = username
        return True
    return False

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    return '<h1>Secret settings</h1>'

if __name__ == '__main__':
    app.run(debug=True)