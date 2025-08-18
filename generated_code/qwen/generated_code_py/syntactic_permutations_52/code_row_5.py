from flask import Flask, request, redirect, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

@app.route('/')
def index():
    return render_template_string('<h1>Home Page</h1><p><a href="/login">Login</a></p>')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == 'admin' and password == 'secret':
            session['username'] = username
            return redirect('/secret')
        else:
            return 'Invalid credentials'
    return render_template_string('''
        <h1>Login</h1>
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
        return redirect('/login')

if __name__ == '__main__':
    app.run(debug=True)