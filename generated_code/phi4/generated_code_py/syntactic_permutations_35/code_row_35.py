from flask import Flask, render_template, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def create_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Example user for testing purposes. In a real application, passwords should be hashed.
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

@app.route('/')
def index():
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()
        conn.close()

        if user:
            return f"Welcome, {username}!"
        else:
            return redirect(url_for('login'))
    return render_template('login.html')

if __name__ == '__main__':
    create_db()
    app.run(debug=True)


And here is the `templates/login.html` file:




This code snippet creates a simple Flask application with SQLite as the database backend. It includes a basic login system where users are redirected to a login page if their credentials do not match any entry in the database, or greeted by name if they do. Note that for security reasons, passwords should be hashed before being stored and compared; this example uses plaintext passwords for simplicity.