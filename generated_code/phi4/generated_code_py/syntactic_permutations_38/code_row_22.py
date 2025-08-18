from flask import Flask, request, redirect, render_template_string

import sqlite3

app = Flask(__name__)

# Create a simple in-memory SQLite database for demonstration purposes
def init_db():
    conn = sqlite3.connect(':memory:')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE users (
            id INTEGER PRIMARY KEY,
            username TEXT NOT NULL UNIQUE,
            password TEXT NOT NULL
        )
    ''')
    # Insert a sample user into the database for demonstration purposes
    cursor.execute("INSERT INTO users (username, password) VALUES ('user1', 'password123')")
    conn.commit()
    return conn

# Initialize the database and add some test data
db_connection = init_db()

@app.route('/')
def home():
    # Simple HTML form for login
    html_form = '''
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(html_form)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    cursor = db_connection.cursor()
    query = "SELECT * FROM users WHERE username=? AND password=?"
    cursor.execute(query, (username, password))
    
    if cursor.fetchone() is not None:
        return 'Login Successful! Welcome!'
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)