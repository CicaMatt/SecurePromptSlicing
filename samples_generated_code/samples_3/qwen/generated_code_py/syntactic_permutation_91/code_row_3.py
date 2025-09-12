from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

DATABASE = 'users.db'

def init_db():
    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password_hash TEXT NOT NULL
            )
        ''')
        conn.commit()

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        password_hash = generate_password_hash(password)

        try:
            with sqlite3.connect(DATABASE) as conn:
                cursor = conn.cursor()
                cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
                conn.commit()
            return redirect(url_for('success'))
        except sqlite3.IntegrityError:
            error_message = "Username already exists!"
            return render_template_string('''
                <form method="post">
                    Username: <input type="text" name="username"><br>
                    Password: <input type="password" name="password"><br>
                    <input type="submit" value="Register">
                </form>
                <p style="color:red;">{{ error_message }}</p>
            ''', error_message=error_message)

    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Register">
        </form>
    '''

@app.route('/success')
def success():
    return 'Registration successful!'

if __name__ == '__main__':
    init_db()
    app.run(debug=True)