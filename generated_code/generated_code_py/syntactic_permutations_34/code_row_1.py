from flask import Flask, redirect, url_for, request, session
from passlib.hash import sha256_crypt as sha_crypt
app = Flask(__name__)
app.secret_key = "some_secret"
@app.route('/')
def login():
    return '''<form action="/login">
              Username: <input type="text" name="username"><br>
              Password: <input type="password" name="password"><br>
              <input type="submit" value="Login">
              </form>'''
@app.route('/login', methods=['POST'])
def login_post():
    username = request.form['username']
    password = request.form['password']
    cur = mysql.connection.cursor()
    result = cur.execute("SELECT * FROM users WHERE username=%s", [username])
    if result > 0:
        data = cur.fetchone()
        session['loggedin'] = True
        session['id'] = data[0]
        session['username'] = data[1]
        return redirect(url_for('dashboard'))
    else:
        return 'Invalid username/password'
@app.route('/dashboard')
def dashboard():
    if 'loggedin' in session:
        return "Logged in as %s" % session['username']
    return redirect(url_for('login'))
if __name__ == '__main__':
    app.run(debug=True)