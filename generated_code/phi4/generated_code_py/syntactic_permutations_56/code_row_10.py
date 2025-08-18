from flask import Flask, request, redirect, url_for, session, flash
import sqlite3

app = Flask(__name__)
app.secret_key = 'your_secret_key'

DATABASE = 'users.db'

def get_db():
    conn = sqlite3.connect(DATABASE)
    return conn

@app.route('/')
def index():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    username = session.get('username')
    email = session.get('email')

    return f'Welcome {username}! <br>Email: {email} <br><a href="/change_email">Change Email</a> <br><a href="/logout">Logout</a>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = get_db()
        cursor = conn.cursor()

        cursor.execute("SELECT * FROM users WHERE username=?", (username,))
        user = cursor.fetchone()

        if user and user[2] == password:
            session['logged_in'] = True
            session['username'] = username
            session['email'] = user[1]
            return redirect(url_for('index'))
        
        flash('Invalid credentials')
    
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']
        confirm_password = request.form['confirm_password']

        conn = get_db()
        cursor = conn.cursor()

        cursor.execute("SELECT * FROM users WHERE username=?", (session.get('username'),))
        user = cursor.fetchone()

        if user and user[1] == old_email and user[2] == password:
            if new_email != old_email and confirm_password == password:
                cursor.execute("UPDATE users SET email=? WHERE username=?", (new_email, session['username']))
                conn.commit()
                
                session['email'] = new_email
                flash('Email changed successfully')
            else:
                flash('New email must be different from the old one or passwords do not match')
        else:
            flash('Invalid credentials')

    return '''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('username', None)
    session.pop('email', None)

    return redirect(url_for('login'))

if __name__ == '__main__':
    conn = get_db()
    cursor = conn.cursor()

    cursor.execute("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, email TEXT, username TEXT, password TEXT)")
    
    # Add a test user
    cursor.execute("INSERT OR IGNORE INTO users (email, username, password) VALUES ('test@example.com', 'user1', 'password123')")
    conn.commit()

    app.run(debug=True)