from flask import Flask, redirect, url_for, request, session
import os

app = Flask(__name__)
app.config['SECRET_KEY'] = 'mysecretkey'

@app.route('/')
def index():
    return "<a href='/login'>Login</a>"

@app.route('/login', methods=['POST', 'GET'])
def do_login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username != 'admin' or password != 'admin':
            error = 'Invalid credentials'
        else:
            session['logged_in'] = True
            return redirect(url_for('secret'))
    return '''
                <form method="post">
                  <p>Username: <input type=text name=username></p>
                  <p>Password: <input type=password name=password></p>
                  <p><input type=submit value=Login></p>
                </form>
            '''

@app.route('/secret')
def secret():
    if not session.get('logged_in'):
        return redirect(url_for('do_login'))
    return "Secret settings"

if __name__ == '__main__':
    app.run()