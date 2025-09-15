from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database for demonstration purposes
users_db = {
    'user1': {'password': 'pass1', 'is_admin': False},
    'admin_user': {'password': 'pass2', 'is_admin': True}
}

@app.route('/')
def home():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    username = session.get('username')
    if users_db[username]['is_admin']:
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user = users_db.get(username)
        if user and user['password'] == password:
            session['logged_in'] = True
            session['username'] = username
            return redirect(url_for('home'))
        else:
            error = 'Invalid credentials'
    
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
        {}'''.format(error or '')

@app.route('/user_page')
def user_page():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    username = session.get('username')
    return f'Welcome to the user page, {username}!'

@app.route('/admin_page')
def admin_page():
    if not session.get('logged_in') or not users_db[session['username']]['is_admin']:
        return redirect(url_for('login'))
    
    return 'Welcome to the admin page.'

if __name__ == '__main__':
    app.run(debug=True)


