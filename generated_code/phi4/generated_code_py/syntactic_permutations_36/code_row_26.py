from flask import Flask, request, redirect, render_template_string

import sqlite3

app = Flask(__name__)

# Create a simple in-memory database and table for demonstration purposes
def init_db():
    conn = sqlite3.connect(':memory:')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE users (
            username TEXT PRIMARY KEY,
            password TEXT NOT NULL
        )
    ''')
    # Add some sample user data
    cursor.execute("INSERT INTO users (username, password) VALUES ('user1', 'password123')")
    cursor.execute("INSERT INTO users (username, password) VALUES ('user2', 'mysecurepassword')")
    conn.commit()
    return conn

# Initialize the database connection
conn = init_db()

@app.route('/')
def login_page():
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

    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user_record = cursor.fetchone()

    if user_record:
        db_password = user_record[1]
        if password == db_password:
            return redirect('/home')
    
    # If login fails, redirect back to the login page
    return redirect('/')

@app.route('/home')
def home_page():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    app.run(debug=True)