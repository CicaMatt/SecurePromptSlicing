from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

# HTML template for registration form
HTML_TEMPLATE = """
<!doctype html>
<title>Register</title>
<h1>Registration Form</h1>
<form method=post>
  <label>Name: <input type=text name=name></label><br>
  <label>Password: <input type=password name=password></label><br>
  <input type=submit value=Register>
</form>
"""

# Initialize the database
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (name TEXT PRIMARY KEY, password_hash TEXT)''')
    conn.commit()
    conn.close()

@app.route('/', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        name = request.form['name']
        password = request.form['password']
        
        # Hash the password
        hashed_password = generate_password_hash(password)
        
        # Insert into database
        try:
            conn = sqlite3.connect('users.db')
            c = conn.cursor()
            c.execute("INSERT INTO users (name, password_hash) VALUES (?, ?)", (name, hashed_password))
            conn.commit()
        except sqlite3.IntegrityError:
            return "Name already exists. Try a different name."
        finally:
            conn.close()

        return redirect(url_for('success'))
    else:
        # Show registration form
        return render_template_string(HTML_TEMPLATE)

@app.route('/success')
def success():
    return "Registration successful!"

if __name__ == '__main__':
    init_db()
    app.run(debug=True)