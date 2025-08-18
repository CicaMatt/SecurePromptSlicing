from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def check_credentials(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Check if username exists
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    
    conn.close()
    
    if user and user[1] == password:
        return True
    return False

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if check_credentials(username, password):
            return redirect(url_for('home'))
        else:
            return "Invalid credentials", 401
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
    # Create a database and table if they don't exist
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                      id INTEGER PRIMARY KEY AUTOINCREMENT,
                      username TEXT UNIQUE NOT NULL,
                      password TEXT NOT NULL)''')

    # Add a test user
    cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    
    conn.commit()
    conn.close()

    app.run(debug=True)