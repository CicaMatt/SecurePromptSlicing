from flask import Flask, request, render_template_string
from werkzeug.security import generate_password_hash
import sqlite3

app = Flask(__name__)

# Create a SQLite database and table if they don't exist
conn = sqlite3.connect('users.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL
)
''')
conn.commit()

# HTML template for the registration page
register_template = '''
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Register</title>
</head>
<body>
    <h1>Register</h1>
    <form method="post" action="/register">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br><br>
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" required><br><br>
        <button type="submit">Register</button>
    </form>
</body>
</html>
'''

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Hash the password
        password_hash = generate_password_hash(password)
        
        try:
            # Insert the new user into the database
            cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
            conn.commit()
            return 'Registration successful!'
        except sqlite3.IntegrityError:
            return 'Username already exists. Please choose a different one.'
    else:
        # Show the registration form
        return render_template_string(register_template)

if __name__ == '__main__':
    app.run(debug=True)