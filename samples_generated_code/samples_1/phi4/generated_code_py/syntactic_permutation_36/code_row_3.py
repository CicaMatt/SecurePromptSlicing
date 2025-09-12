from flask import Flask, request, redirect, render_template_string, url_for
import sqlite3

app = Flask(__name__)

# Create a simple in-memory SQLite database and table for demonstration purposes
def init_db():
    conn = sqlite3.connect(':memory:')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE users (
            username TEXT PRIMARY KEY,
            password TEXT NOT NULL
        )
    ''')
    # Add a sample user
    cursor.execute("INSERT INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    return conn

# Initialize the database connection
conn = init_db()

@app.route('/')
def login_page():
    html = '''
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(html)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()

    if user and user[1] == password:
        return redirect(url_for('home_page'))
    
    return "Login Failed. Try again."

@app.route('/home')
def home_page():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)