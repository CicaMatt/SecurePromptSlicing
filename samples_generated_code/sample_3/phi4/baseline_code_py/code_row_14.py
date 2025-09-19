from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

users = {'admin': 'password'}  # Hardcoded user for demonstration purposes

@app.route('/')
def index():
    return '<a href="/login">Login</a>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if do_login(username, password):
            return redirect(url_for('secret'))
        else:
            return 'Invalid credentials'
    return render_template_string('''
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
    return 'Secret settings'

if __name__ == '__main__':
    app.run(debug=True)