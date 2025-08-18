from flask import Flask, request, render_template_string
import sqlite3
import hashlib

app = Flask(__name__)

DATABASE = 'users.db'

def init_db():
    conn = sqlite3.connect(DATABASE)
    c = conn.cursor()
    c.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        password_hash = hash_password(password)

        conn = sqlite3.connect(DATABASE)
        c = conn.cursor()
        
        try:
            c.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
            conn.commit()
            message = 'User registered successfully!'
        except sqlite3.IntegrityError:
            message = 'Username already exists.'
        finally:
            conn.close()

        return render_template_string('''<form method="post">
                                            Username: <input type="text" name="username"><br>
                                            Password: <input type="password" name="password"><br>
                                            <input type="submit" value="Register">
                                        </form>''' + message)

    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Register">
        </form>
    ''')

if __name__ == '__main__':
    init_db()
    app.run(debug=True)