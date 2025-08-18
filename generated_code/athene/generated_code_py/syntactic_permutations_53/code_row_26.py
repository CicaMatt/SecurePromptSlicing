from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user_id' not in session:
        return redirect(url_for('login'))
    elif session['role'] == 'admin':
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('user'))

@app.route('/login')
def login():
    # Simulate logging in
    session['user_id'] = 1
    session['role'] = 'user'
    return "Login page"

@app.route('/user')
def user():
    if 'user_id' not in session or session['role'] != 'user':
        return redirect(url_for('login'))
    return "User page"

@app.route('/admin')
def admin():
    if 'user_id' not in session or session['role'] != 'admin':
        return redirect(url_for('index'))
    return "Admin page"

if __name__ == '__main__':
    app.run(debug=True)