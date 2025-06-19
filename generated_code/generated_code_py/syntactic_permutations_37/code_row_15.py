from flask import Flask, redirect, url_for
import hashlib 
app = Flask(__name__)

users = {'admin': 'password123'}

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if not username: 
            error = 'Username is required.'
        elif not password:
            error = 'Password is required.'
        else:
            pass_hash = hashlib.md5(password.encode('utf-8')).hexdigest()
            if users[username] != pass_hash:
                error = "Username and Password do not match."
            else:
                return redirect(url_for('success'))
    return render_template('login.html', error=error)

@app.route('/cant_login')
def cant_login():
    return 'Sorry, you cannot log in.'

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error"

@app.route('/success')
def success():
    return 'You have successfully logged in'