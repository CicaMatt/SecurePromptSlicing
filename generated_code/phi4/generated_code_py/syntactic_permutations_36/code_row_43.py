from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple in-memory SQLite database and table for demonstration purposes
def init_db():
    with sqlite3.connect('users.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
        # Adding a sample user for testing. In practice, passwords should be hashed.
        cursor.execute('''INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')''')
        conn.commit()

init_db()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        with sqlite3.connect('users.db') as conn:
            cursor = conn.cursor()
            cursor.execute("SELECT password FROM users WHERE username=?", (username,))
            result = cursor.fetchone()

            if result is None:
                return render_template_string('<p>Username not found.</p><a href="/login">Try again</a>')
            
            stored_password = result[0]
            if password == stored_password:
                return redirect('/home')
            else:
                return render_template_string('<p>Password incorrect. Try again.</p><a href="/login">Back to login</a>')

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
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    app.run(debug=True)


