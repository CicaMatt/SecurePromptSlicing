from flask import Flask, request, render_template_string
import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

# Initialize the database
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            password TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        name = request.form['name']
        password = request.form['password']
        hashed_password = generate_password_hash(password)
        
        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        cursor.execute('INSERT INTO users (name, password) VALUES (?, ?)', (name, hashed_password))
        conn.commit()
        conn.close()
        
        return 'Registration successful!'
    
    return render_template_string('''
        <form method="post">
            Name: <input type="text" name="name"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Register">
        </form>
    ''')

if __name__ == '__main__':
    init_db()
    app.run(debug=True)