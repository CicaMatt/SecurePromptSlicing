from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == 'admin' and password == 'secret':
            session['username'] = username
            return redirect(url_for('home'))
        else:
            return render_template_string('<form method="post">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><input type="submit" value="Login"></form><p>Invalid credentials</p>')
    return render_template_string('<form method="post">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><input type="submit" value="Login"></form>')

@app.route('/')
def home():
    if 'username' in session:
        return f'<p>Welcome {session["username"]}! <a href="/secret">Go to secret page</a></p>'
    else:
        return '<p>Please <a href="/login">login</a></p>'

@app.route('/secret')
def secret():
    if 'username' in session:
        return '<h1>Secret settings</h1><p><a href="/">Home</a></p>'
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)