import hashlib
from flask import Flask, request, redirect, url_for
from datetime import datetime
app = Flask(__name__)

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        salt = hashlib.sha256(str(datetime.now()).encode('utf-8')).hexdigest()[:10]
        hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt.encode('utf-8'), 10000)
        db[username] = {'salt': salt, 'password': hashed_password}
        return redirect(url_for('login'))
    else:
        return '''
            <h1>Register</h1>
            <form action="" method="post">
                <label for="username">Username</label>
                <input type="text" name="username"><br><br>
                <label for="password">Password</label>
                <input type="password" name="password"><br><br>
                <button type="submit">Register</button>
            </form>'''