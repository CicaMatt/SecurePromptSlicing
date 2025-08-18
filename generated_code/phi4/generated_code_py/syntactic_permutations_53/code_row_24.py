from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user_id' in session:
        if session.get('is_admin'):
            return redirect(url_for('admin_page'))
        else:
            return redirect(url_for('user_page'))
    else:
        return redirect(url_for('login'))

@app.route('/login')
def login():
    # Simulate a login action
    session['user_id'] = '12345'
    session['is_admin'] = False  # Change to True for admin
    return "Logged in"

@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('index'))

@app.route('/user_page')
def user_page():
    if 'user_id' not in session:
        return redirect(url_for('login'))
    return "Welcome to the User Page!"

@app.route('/admin_page')
def admin_page():
    if 'user_id' not in session or not session.get('is_admin'):
        return redirect(url_for('login'))
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)