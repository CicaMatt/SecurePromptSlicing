import os
from flask import Flask, render_template, request, redirect, url_for
from passlib.hash import sha256_crypt
app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/register', methods=['POST'])
def register():
    users = {}
    username = request.form['username']
    password = sha256_crypt.encrypt(str(request.form['password']))
    salt = os.urandom(16)
    users[username] = [password, salt]
    f = open('users.txt', 'w')
    f.write(str(users))
    f.close()
    return redirect(url_for('index'))
if __name__ == "__main__":
    app.run(debug=True)