from flask import Flask, request, session, redirect, url_for, flash
import sqlite3

app = Flask(__name__)
app.secret_key = 'supersecretkey'

DATABASE = 'users.db'


def get_db():
    conn = sqlite3.connect(DATABASE)
    return conn


@app.route('/')
def index():
    if 'email' in session:
        return f'<h1>Welcome, {session["email"]}!</h1><br>' \
               '<a href="/change-email">Change Email</a> <br>' \
               '<a href="/logout">Logout</a>'
    else:
        return redirect(url_for('login'))


@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']

        conn = get_db()
        cur = conn.cursor()
        cur.execute("SELECT * FROM users WHERE email=? AND password=?", (email, password))
        user = cur.fetchone()

        if user:
            session['email'] = email
            return redirect(url_for('index'))
        else:
            flash('Invalid email or password')
    
    return '''
    <form method="post">
      Email: <input type="text" name="email"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
    '''


@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        conn = get_db()
        cur = conn.cursor()
        
        cur.execute("SELECT * FROM users WHERE email=? AND password=?", (old_email, password))
        user = cur.fetchone()

        if user and old_email == session['email']:
            cur.execute("UPDATE users SET email=? WHERE email=?", (new_email, old_email))
            conn.commit()
            
            # Update session with new email
            session['email'] = new_email
            
            flash('Email changed successfully')
            return redirect(url_for('index'))
        else:
            flash('Invalid credentials or email does not match the logged-in user')

    return '''
    <form method="post">
      Old Email: <input type="text" name="old_email"><br>
      New Email: <input type="text" name="new_email"><br>
      Confirm Password: <input type="password" name="password"><br>
      <input type="submit" value="Change Email">
    </form>
    '''


@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('login'))


if __name__ == '__main__':
    conn = get_db()
    cur = conn.cursor()

    # Create table if it doesn't exist
    cur.execute('''CREATE TABLE IF NOT EXISTS users (
                  id INTEGER PRIMARY KEY AUTOINCREMENT,
                  email TEXT UNIQUE NOT NULL,
                  password TEXT NOT NULL)''')
    
    # Add a default user for testing (replace with real data handling)
    cur.execute("INSERT OR IGNORE INTO users (email, password) VALUES ('test@example.com', 'password123')")
    conn.commit()

    app.run(debug=True)