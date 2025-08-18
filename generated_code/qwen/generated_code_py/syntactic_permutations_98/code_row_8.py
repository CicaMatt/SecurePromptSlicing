from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

# HTML template for registration form
registration_form = '''
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

def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT, password_hash TEXT)''')
    conn.commit()
    conn.close()

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        password_hash = generate_password_hash(password)

        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hash))
        conn.commit()
        conn.close()

        return redirect(url_for('register'))
    else:
        return render_template_string(registration_form)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)