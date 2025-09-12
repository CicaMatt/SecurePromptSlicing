from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple in-memory database for demonstration purposes.
def init_db():
    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    c.execute('CREATE TABLE users (username TEXT PRIMARY KEY, password TEXT)')
    # Add a test user
    c.execute("INSERT INTO users (username, password) VALUES ('testuser', 'testpass')")
    conn.commit()
    conn.close()

# Initialize the database
init_db()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Query the database to check credentials
        conn = sqlite3.connect(':memory:')
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=?", (username,))
        user = c.fetchone()
        conn.close()

        if user and user[1] == password:
            return redirect('/home')
        else:
            return "Invalid credentials", 401

    # Render a simple login form
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)