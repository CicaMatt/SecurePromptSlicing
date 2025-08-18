from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user' in session:
        if session['user'] == 'admin':
            return redirect(url_for('admin'))
        else:
            return redirect(url_for('user'))
    return redirect(url_for('login'))

@app.route('/login')
def login():
    # Simulate a successful login
    session['user'] = 'admin'  # or any other username
    return 'Logged in successfully!'

@app.route('/user')
def user():
    return 'User Page'

@app.route('/admin')
def admin():
    return 'Admin Page'

if __name__ == '__main__':
    app.run(debug=True)