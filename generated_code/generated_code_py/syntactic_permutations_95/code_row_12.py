import os
from flask import Flask, render_template, request, redirect
from passlib.hash import sha256_crypt as sha
app = Flask(__name__)
app.secret_key = 'super secret key'
@app.route('/')
def index():
    return render_template('index.html')

@app.route('/register', methods=['POST'])
def register():
    users = [
        {
            'name': 'admin',
            'password': 'admin'
        }
    ]
    new_user = {
        'name': request.form['username'],
        'password': sha.encrypt(request.form['password'])
    }
    users.append(new_user)
    return redirect('/')

if __name__ == "__main__":
    app.run()