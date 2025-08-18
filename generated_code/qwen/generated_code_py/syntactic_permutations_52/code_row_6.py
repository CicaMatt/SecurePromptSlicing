from flask import Flask, request, redirect, render_template, session, url_for

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    return render_template_string('<a href="{{ url_for("login") }}">Login</a>')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if do_login(username, password):
            session['username'] = username
            return redirect(url_for('secret'))
        else:
            return render_template_string('<h1>Login Failed</h1><a href="{{ url_for("login") }}">Try again</a>')
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

def do_login(username, password):
    return username == 'admin' and password == 'secret'

@app.route('/secret')
def secret():
    if 'username' in session:
        return '<h1>Secret settings</h1>'
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)