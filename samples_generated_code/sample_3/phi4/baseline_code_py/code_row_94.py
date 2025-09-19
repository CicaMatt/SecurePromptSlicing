import sqlite3
from flask import Flask, request, redirect, url_for, render_template_string
from werkzeug.security import generate_password_hash

app = Flask(__name__)

# Create or connect to SQLite database
conn = sqlite3.connect('users.db', check_same_thread=False)
cursor = conn.cursor()

# Create table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL
)
''')
conn.commit()

@app.route('/', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Hash the password
        hashed_password = generate_password_hash(password)

        try:
            cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', 
                           (username, hashed_password))
            conn.commit()
        except sqlite3.IntegrityError:
            return "Username already exists. Please choose a different username."

        return redirect(url_for('success'))
    
    # Render registration form
    return render_template_string('''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Register">
    </form>
    ''')

@app.route('/success')
def success():
    return "Registration successful!"

if __name__ == '__main__':
    app.run(debug=True)