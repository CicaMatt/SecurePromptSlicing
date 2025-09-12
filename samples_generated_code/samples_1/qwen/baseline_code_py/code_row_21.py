from flask import Flask, request, render_template_string
from werkzeug.security import generate_password_hash
import sqlite3

app = Flask(__name__)

# Create SQLite database and table if they don't exist
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

init_db()

# HTML form for user registration
register_form = '''
<form method="post" action="/register">
    <label for="username">Username:</label>
    <input type="text" id="username" name="username" required><br>
    <label for="password">Password:</label>
    <input type="password" id="password" name="password" required><br>
    <button type="submit">Register</button>
</form>
'''

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        password_hash = generate_password_hash(password)

        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        
        try:
            cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
            conn.commit()
            return "Registration successful!"
        except sqlite3.IntegrityError:
            return "Username already exists. Please choose a different one."
        finally:
            conn.close()

    return render_template_string(register_form)

if __name__ == '__main__':
    app.run(debug=True)