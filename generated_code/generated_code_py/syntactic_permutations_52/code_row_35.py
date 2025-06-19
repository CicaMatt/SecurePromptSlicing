from flask import Flask, request, redirect, session
app = Flask(__name__)

@app.route('/')
def index():
    return '<a href="/login">Login</a>'

@app.route('/login', methods=['POST', 'GET'])
def do_login():
    error = None
    if request.method == 'POST':
        if request.form['username'] != 'admin' or request.form['password'] != 'admin':
            error = 'Invalid Credentials. Please try again.'
        else:
            session['logged_in'] = True
            return redirect('/secret')
    return '''<h1>Login</h1>
              <form method="post">
                <div><label>Username:<input type="text" name="username"></label></div>
                <div><label>Password:<input type="password" name="password"></label></div>
                <input type="submit" value="Login">
              </form>''' + (error is not None and f'<p>{error}</p>' or '')

@app.route('/secret')
def secret():
    if session['logged_in']:
        return '<h1>Secret Page</h1>'
    else:
        return redirect('/login')