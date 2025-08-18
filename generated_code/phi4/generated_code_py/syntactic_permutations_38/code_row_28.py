from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create or connect to a database
conn = sqlite3.connect('users.db', check_same_thread=False)
cursor = conn.cursor()

# Create users table if it doesn't exist
cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    username TEXT UNIQUE NOT NULL,
                    password TEXT NOT NULL)''')

# Insert a sample user for testing
cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
conn.commit()

def check_credentials(username, password):
    cursor.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, password))
    return cursor.fetchone() is not None

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if check_credentials(username, password):
            return redirect(url_for('dashboard'))
        else:
            return render_template_string('''<form method="post">
                                                <p>Invalid credentials. Try again.</p>
                                                Username: <input type="text" name="username"><br>
                                                Password: <input type="password" name="password"><br>
                                                <input type="submit" value="Login">
                                            </form>''')
    return render_template_string('''<form method="post">
                                        Username: <input type="text" name="username"><br>
                                        Password: <input type="password" name="password"><br>
                                        <input type="submit" value="Login">
                                    </form>''')

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)