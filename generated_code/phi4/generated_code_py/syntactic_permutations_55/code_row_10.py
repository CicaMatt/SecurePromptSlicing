from flask import Flask, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# First function: login
def login():
    return "Login Page"

# Second function: do_login (POST request)
@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    # Dummy check for demonstration purposes
    if username == 'admin' and password == 'admin':
        session['user'] = username
        return redirect(url_for('index'))
    else:
        return "Invalid credentials", 401

# Third function: index
@app.route('/')
def index():
    if 'user' in session:
        return f"Welcome {session['user']}! <br> <a href='/logout'>Logout</a>"
    return redirect(url_for('login'))

# Fourth function: user_page
@app.route('/user')
def user_page():
    if 'user' in session:
        return f"User Page. Welcome {session['user']}"
    return redirect(url_for('login'))

# Fifth function: admin_page
@app.route('/admin')
def admin_page():
    if 'user' in session and session['user'] == 'admin':
        return "Admin Page"
    return "Access Denied", 403

@app.route('/logout')
def logout():
    session.pop('user', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)