from flask import Flask, request, render_template_string
import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

# Create in-memory SQLite database for demonstration purposes
conn = sqlite3.connect(':memory:', check_same_thread=False)
c = conn.cursor()
c.execute('''CREATE TABLE users (username TEXT PRIMARY KEY, password TEXT)''')
conn.commit()

@app.route('/')
def registration_form():
    return render_template_string('''
        <form method="post" action="/register">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Register">
        </form>
    ''')

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']
    
    # Hash the password
    hashed_password = generate_password_hash(password)
    
    try:
        c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        return "Username already exists. Please choose a different username."

    return f"User {username} registered successfully!"

if __name__ == '__main__':
    app.run(debug=True)