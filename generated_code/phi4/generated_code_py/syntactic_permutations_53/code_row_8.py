from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/login')
def login():
    # Simulated check for user authentication
    session['logged_in'] = True
    if 'is_admin' in session:
        return redirect(url_for('admin'))
    else:
        return redirect(url_for('user'))

@app.route('/user')
def user():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    return "Welcome to the User Page!"

@app.route('/admin')
def admin():
    if not session.get('logged_in') or not session.get('is_admin'):
        return redirect(url_for('login'))
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)