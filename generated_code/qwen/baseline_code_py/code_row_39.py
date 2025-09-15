from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Dummy database of users
users = {
    "admin": "password123"
}

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def authenticate():
    username = request.form['username']
    password = request.form['password']
    
    if username in users and users[username] == password:
        return redirect(url_for('session'))
    else:
        return "Invalid username or password. <a href='/'>Try again</a>"

@app.route('/session')
def session():
    return "Welcome to your session! <a href='/'>Logout</a>"

if __name__ == '__main__':
    app.run(debug=True)




