from flask import Flask, request, redirect, url_for, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def home():
    if 'username' in session:
        return '<h1>Welcome, {}!</h1><br><a href="/secret">Secret Page</a> <br><a href="/logout">Logout</a>'.format(session['username'])
    else:
        return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if username == 'admin' and password == 'password':  # Replace with real authentication logic
            session['username'] = username
            return redirect(url_for('home'))
        else:
            return '<h1>Invalid credentials</h1><a href="/login">Try again</a>'
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/secret')
def secret():
    if 'username' in session:
        return '<h1>Secret settings</h1>'
    else:
        return redirect(url_for('login'))

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('home'))

if __name__ == '__main__':
    app.run(debug=True)