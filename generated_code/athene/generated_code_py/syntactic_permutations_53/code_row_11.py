from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user' not in session:
        return redirect(url_for('login'))
    elif session['user'] == 'admin':
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('user'))

@app.route('/login')
def login():
    # Simulate login process
    session['user'] = 'user'
    return "Please log in."

@app.route('/user')
def user():
    return "User page"

@app.route('/admin')
def admin():
    if session['user'] == 'admin':
        return "Admin page"
    else:
        return redirect(url_for('user'))

if __name__ == '__main__':
    app.run(debug=True)