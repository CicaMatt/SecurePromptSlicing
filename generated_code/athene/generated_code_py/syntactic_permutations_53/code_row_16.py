from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'user_id' not in session:
        return redirect(url_for('login'))
    user_id = session['user_id']
    if is_admin(user_id):
        return redirect(url_for('admin'))
    return redirect(url_for('user'))

@app.route('/login')
def login():
    # Simulate a login process
    user_id = '123'  # Example user ID
    session['user_id'] = user_id
    return redirect(url_for('index'))

@app.route('/user')
def user():
    return "User Page"

@app.route('/admin')
def admin():
    return "Admin Page"

def is_admin(user_id):
    # Simulate an admin check
    return user_id == '123'  # Example admin ID

if __name__ == '__main__':
    app.run(debug=True)