from flask import Flask, request, render_template_string
from werkzeug.security import generate_password_hash
import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

def init_db():
    with sqlite3.connect(DATABASE) as conn:
        conn.execute('CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password TEXT)')
        conn.commit()

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        hashed_password = generate_password_hash(password)
        
        try:
            with sqlite3.connect(DATABASE) as conn:
                conn.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, hashed_password))
                conn.commit()
                return "Registration successful!"
        except sqlite3.IntegrityError:
            return "Username already exists!"
    
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