from flask import Flask, request, render_template_string, redirect, url_for, flash
from werkzeug.security import generate_password_hash
import sqlite3

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# HTML template for registration form
HTML_TEMPLATE = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Register</title>
  </head>
  <body>
    <h1>Register</h1>
    {% with messages = get_flashed_messages() %}
      {% if messages %}
        <ul>
          {% for message in messages %}
            <li>{{ message }}</li>
          {% endfor %}
        </ul>
      {% endif %}
    {% endwith %}
    <form method="post">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Register">
    </form>
  </body>
</html>
'''

@app.route('/', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Hash the password
        hashed_password = generate_password_hash(password)

        # Connect to SQLite database and insert user
        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        
        try:
            cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
            cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, hashed_password))
            conn.commit()
            flash('User registered successfully!')
        except sqlite3.IntegrityError:
            flash('Username already exists. Please choose another one.')
        
        conn.close()

        return redirect(url_for('register'))

    return render_template_string(HTML_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)