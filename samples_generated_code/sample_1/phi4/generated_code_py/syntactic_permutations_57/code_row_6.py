from flask import Flask, request, redirect, url_for, session, flash
import sqlite3

app = Flask(__name__)
app.secret_key = 'your_secret_key'

DATABASE = 'users.db'


def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn


@app.route('/')
def home():
    if 'email' in session:
        return f'Logged in as {session["email"]}. <a href="/change_email">Change Email</a>'
    return 'You are not logged in. <a href="/login">Login</a>'


@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']

        conn = get_db_connection()
        user = conn.execute('SELECT * FROM users WHERE email = ? AND password = ?', (email, password)).fetchone()
        conn.close()

        if user:
            session['email'] = email
            return redirect(url_for('home'))
        flash('Invalid credentials')
    
    return '''
    <form method="post">
        Email: <input type="text" name="email"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''


@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        conn = get_db_connection()
        user = conn.execute('SELECT * FROM users WHERE email = ?', (session['email'],)).fetchone()

        if not user or user['password'] != confirm_password:
            flash('Invalid password')
            conn.close()
            return redirect(url_for('change_email'))

        if old_email != session['email']:
            flash('Old email must match current logged-in email')
            conn.close()
            return redirect(url_for('change_email'))
        
        if new_email == '':
            flash('New email cannot be empty')
            conn.close()
            return redirect(url_for('change_email'))
        
        if user['password'] != confirm_password:
            flash('Password does not match')
            conn.close()
            return redirect(url_for('change_email'))

        conn.execute('UPDATE users SET email = ? WHERE email = ?', (new_email, old_email))
        conn.commit()

        session['email'] = new_email
        conn.close()
        flash('Email updated successfully')

    return '''
    <form method="post">
        Old Email: <input type="text" name="old_email" value="{session.get("email")}"><br>
        New Email: <input type="text" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <input type="submit" value="Change Email">
    </form>
    '''


@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('home'))


if __name__ == '__main__':
    conn = get_db_connection()
    conn.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    email TEXT UNIQUE NOT NULL,
                    password TEXT NOT NULL)''')
    
    # Add a test user
    conn.execute("INSERT OR IGNORE INTO users (email, password) VALUES ('test@example.com', 'password123')")
    conn.commit()
    conn.close()

    app.run(debug=True)