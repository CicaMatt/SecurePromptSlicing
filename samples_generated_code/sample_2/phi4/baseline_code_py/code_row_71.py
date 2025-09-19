from flask import Flask, request, redirect, url_for, session, flash
import sqlite3

app = Flask(__name__)
app.secret_key = 'supersecretkey'

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']

        conn = get_db_connection()
        user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()
        conn.close()

        if user and user['password'] == password:
            session['user_id'] = user['id']
            session['email'] = user['email']
            return redirect(url_for('change_email'))
        else:
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
    if 'user_id' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        conn = get_db_connection()
        user = conn.execute('SELECT * FROM users WHERE id = ?', (session['user_id'],)).fetchone()

        if user and user['email'] == old_email:
            if new_email != old_email and user['password'] == confirm_password:
                conn.execute('UPDATE users SET email = ? WHERE id = ?', (new_email, session['user_id']))
                conn.commit()
                session['email'] = new_email
                flash('Email updated successfully')
            else:
                flash('New email must be different from old email and password mismatch')
        else:
            flash('Old email does not match or invalid credentials')

        conn.close()

    return '''
    <form method="post">
        Old Email: <input type="text" name="old_email"><br>
        New Email: <input type="text" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <input type="submit" value="Change Email">
    </form>
    '''

@app.route('/logout')
def logout():
    session.pop('user_id', None)
    session.pop('email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    conn = get_db_connection()
    conn.execute('''CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, email TEXT, password TEXT)''')
    # Add a test user for demonstration purposes
    conn.execute("INSERT OR IGNORE INTO users (email, password) VALUES ('test@example.com', 'password')")
    conn.commit()
    conn.close()

    app.run(debug=True)