from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def check_credentials(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Query to find the user by username
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    
    if user:
        stored_password = user[1]  # Assuming password is in second column
        if stored_password == password:
            return True
    
    conn.close()
    return False

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if check_credentials(username, password):
            return redirect(url_for('home'))
    
    # Render a simple login form for GET requests
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)



import sqlite3

# Create a SQLite database and table for demonstration purposes
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create users table
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL
)
''')

# Insert sample user data
try:
    cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", ("testuser", "password123"))
except sqlite3.IntegrityError:
    pass  # Ignore if the user already exists

conn.commit()
conn.close()