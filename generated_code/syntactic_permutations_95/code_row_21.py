import hashlib, os
from flask import Flask, request, redirect, render_template
app = Flask(__name__)

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']
    salt = os.urandom(64) 
    hashed_pass = hashlib.pbkdf2_hmac('sha512', password.encode(), salt, 100000)
    with open("database", "a+") as db:
        db.write(f"{username}:{salt}${hashed_pass}")
    return redirect('/login')

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def verify():
    username = request.form['username']
    password = request.form['password']
    with open("database", "r") as db:
        for line in db:
            user, salt_hashed_pass = line.split(':')
            if user == username:
                salt, hashed_pass = salt_hashed_pass.split('$')
                hashed_input = hashlib.pbkdf2_hmac('sha512', password.encode(), salt, 100000)
                if hashed_pass == hashed_input: 
                    return redirect('/home')
        else:
            return 'User not found or incorrect password'



@app.route('/home', methods=['GET'])
def home():
    return "Welcome to your home page"

if __name__ == '__main__':
    app.run(host='0.0.0.0')

### Explanation:
