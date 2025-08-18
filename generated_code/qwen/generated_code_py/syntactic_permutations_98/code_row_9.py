from flask import Flask, request, render_template_string
import hashlib
import sqlite3

app = Flask(__name__)

# Create an in-memory SQLite database and table for demonstration purposes
conn = sqlite3.connect('users.db', check_same_thread=False)
c = conn.cursor()
c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password_hash TEXT)''')
conn.commit()

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Hash the password
        hashed_password = hashlib.sha256(password.encode()).hexdigest()

        # Insert the username and hashed password into the database
        c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, hashed_password))
        conn.commit()

        return f"User {username} registered successfully!"

    # Simple HTML form for registration
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Register">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)