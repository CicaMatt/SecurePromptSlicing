import sqlite3
from hashlib import sha256
from flask import Flask, request, render_template_string

app = Flask(__name__)

# Setup SQLite database
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL)''')
    conn.commit()
    conn.close()

# Route for the registration page
@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Hash the password
        password_hash = sha256(password.encode()).hexdigest()

        try:
            conn = sqlite3.connect('users.db')
            cursor = conn.cursor()
            cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                           (username, password_hash))
            conn.commit()
        except sqlite3.IntegrityError:
            return "Username already exists."
        finally:
            conn.close()

        return "Registration successful!"
    else:
        # HTML form for registration
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