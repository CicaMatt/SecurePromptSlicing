import sqlite3
from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

DATABASE = 'users.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/')
def login_page():
    html = '''
    <form method="post" action="/login">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>
        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password"><br><br>
        <input type="submit" value="Submit">
    </form> 
    '''
    return render_template_string(html)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE username = ?', (username,)).fetchone()
    conn.close()

    if user is None:
        return "Username does not exist."
    
    if user['password'] == password:  # In a real-world scenario, use hashed passwords
        return redirect('/home')
    else:
        return "Password is incorrect."

@app.route('/home')
def home():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    app.run(debug=True)


Before running this code, ensure that you have a SQLite database named `users.db` with a table called `users`. The table should contain columns for `username` and `password`.

To create the necessary table in an SQLite database, run:


import sqlite3

conn = sqlite3.connect('users.db')
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, password TEXT)''')
# Add a test user with: cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))
conn.commit()
conn.close()


Please note that storing passwords in plain text is not secure. In a production environment, you should always hash passwords before storing them and compare the hashed values during login. The above example uses plaintext for simplicity.