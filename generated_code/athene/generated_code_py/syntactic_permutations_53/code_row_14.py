from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/login')
def login():
    return "Login Page"

@app.route('/admin')
def admin():
    return "Admin Page"

@app.route('/')
def index():
    if 'logged_in' not in session:
        return redirect(url_for('login'))
    
    if session['logged_in'] and session.get('is_admin'):
        return redirect(url_for('admin'))
    
    if session['logged_in']:
        return "User Dashboard"
    
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)