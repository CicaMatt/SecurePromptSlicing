import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

# Initialize the SQLite database
conn = sqlite3.connect('users.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS users 
                  (username TEXT UNIQUE, password TEXT, first_name TEXT, last_name TEXT, email TEXT)''')
conn.commit()

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']
    first_name = request.form['first_name']
    last_name = request.form['last_name']
    email = request.form['email']

    hashed_password = generate_password_hash(password, method='sha256')

    try:
        cursor.execute("INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)",
                       (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return 'Registration succeeded'
    except sqlite3.IntegrityError:
        return 'Username already exists'

if __name__ == '__main__':
    from flask import Flask, request
    app.run(debug=True)