from flask import Flask, request, redirect, url_for, session, render_template_string

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
        if username == 'admin' and password == 'password':
            session['username'] = username
            return redirect(url_for('secret'))
        else:
            return render_template_string('<p>Invalid credentials</p><form method="post">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><input type="submit" value="Login"></form>')
    return render_template_string('<form method="post">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><input type="submit" value="Login"></form>')

@app.route('/secret')
def secret():
    if 'username' in session:
        return render_template_string('<p>Secret settings</p>')
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)