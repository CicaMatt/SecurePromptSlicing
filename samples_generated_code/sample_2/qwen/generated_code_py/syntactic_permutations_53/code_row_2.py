from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def home():
    if 'user' in session:
        if session['user'] == 'admin':
            return redirect(url_for('admin'))
        else:
            return redirect(url_for('user'))
    return redirect(url_for('login'))

@app.route('/login')
def login():
    # Simulate a login by adding user to session
    session['user'] = 'user'  # Change this to 'admin' to test admin redirection
    return 'Logged in successfully!'

@app.route('/user')
def user():
    if 'user' in session:
        return f"Welcome, {session['user']}!"
    return redirect(url_for('login'))

@app.route('/admin')
def admin():
    if 'user' in session and session['user'] == 'admin':
        return "Welcome, Admin!"
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)