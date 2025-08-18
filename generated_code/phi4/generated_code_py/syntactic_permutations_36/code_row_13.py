from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# HTML templates as strings for simplicity
login_page = """
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
"""

home_page = """
<!doctype html>
<title>Home Page</title>
<h2>Welcome to the Home Page!</h2>
<a href="/logout">Logout</a>
"""

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        
        cursor.execute("SELECT * FROM users WHERE username=?", (username,))
        user_record = cursor.fetchone()
        
        conn.close()

        if user_record and user_record[1] == password:
            return redirect('/home')
        else:
            return "Invalid login credentials", 401

    return render_template_string(login_page)

@app.route('/home')
def home():
    return render_template_string(home_page)

@app.route('/logout')
def logout():
    return redirect('/')

# Create the SQLite database and table if not exists
with sqlite3.connect('users.db') as conn:
    cursor = conn.cursor()
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        )
    """)
    # Insert a sample user for testing purposes (remove or modify in production)
    cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))
    conn.commit()

if __name__ == '__main__':
    app.run(debug=True)