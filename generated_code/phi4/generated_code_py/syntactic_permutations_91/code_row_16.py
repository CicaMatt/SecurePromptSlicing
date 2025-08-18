from flask import Flask, request, render_template_string
import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

# HTML template for registration form
HTML_TEMPLATE = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Register</title>
  </head>
  <body>
    <h2>Register</h2>
    <form method="post">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Register">
    </form>
  </body>
</html>
'''

# Database setup
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

@app.route('/', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Hash the password
        password_hash = generate_password_hash(password)

        # Insert into database
        try:
            conn = sqlite3.connect('users.db')
            c = conn.cursor()
            c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                      (username, password_hash))
            conn.commit()
            conn.close()

            return "Registration successful!"
        except sqlite3.IntegrityError:
            return "Username already exists."

    # Render registration form
    return render_template_string(HTML_TEMPLATE)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)