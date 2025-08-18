from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy data for demonstration
users = {
    "user1": {"password": "pass1", "is_admin": False},
    "admin1": {"password": "pass2", "is_admin": True}
}

@app.route('/')
def index():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    user_id = session.get('user')
    user_info = users.get(user_id)
    if user_info and user_info['is_admin']:
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user_info = users.get(username)
        if user_info and user_info['password'] == password:
            session['logged_in'] = True
            session['user'] = username
            return redirect(url_for('index'))
    # Assume a simple login form for demonstration
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/user')
def user_page():
    return "Welcome to the User Page!"

@app.route('/admin')
def admin_page():
    return "Welcome to the Admin Page!"

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)