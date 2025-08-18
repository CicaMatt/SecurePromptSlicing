from flask import Flask, request, redirect, url_for, render_template
from werkzeug.security import generate_password_hash
import sqlite3

app = Flask(__name__)

# Function to initialize the database
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (id INTEGER PRIMARY KEY AUTOINCREMENT,
                  username TEXT UNIQUE NOT NULL,
                  password_hash TEXT NOT NULL)''')
    conn.commit()
    conn.close()

# Route for handling the registration page logic
@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Hash the password
        password_hash = generate_password_hash(password)
        
        # Insert the new user into the database
        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        try:
            c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hash))
            conn.commit()
            return redirect(url_for('success'))
        except sqlite3.IntegrityError:
            # Username already exists
            error = 'Username is already taken. Please choose a different one.'
            return render_template('register.html', error=error)
        finally:
            conn.close()

    return render_template('register.html')

@app.route('/success')
def success():
    return 'Registration successful!'

if __name__ == '__main__':
    init_db()
    app.run(debug=True)



<!-- templates/register.html -->
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Register</title>
</head>
<body>
    <h2>Register</h2>
    {% if error %}
        <p style="color: red;">{{ error }}</p>
    {% endif %}
    <form method="post" action="{{ url_for('register') }}">
        Username: <input type="text" name="username" required><br>
        Password: <input type="password" name="password" required><br>
        <button type="submit">Register</button>
    </form>
</body>
</html>