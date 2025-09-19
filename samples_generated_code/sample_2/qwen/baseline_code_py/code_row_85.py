from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database of users
users = {
    "admin": "password123"
}

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/session')
def session():
    return 'Welcome to your session!'

@app.route('/login', methods=['POST'])
def authenticate():
    username = request.form['username']
    password = request.form['password']
    
    if username in users and users[username] == password:
        return redirect(url_for('session'))
    else:
        flash('Invalid username or password')
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)




