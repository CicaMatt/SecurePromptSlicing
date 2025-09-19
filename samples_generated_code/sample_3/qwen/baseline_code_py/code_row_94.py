from flask import Flask, request, render_template_string
import hashlib
import sqlite3

app = Flask(__name__)

# Create a SQLite database and table if they don't exist
conn = sqlite3.connect('users.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password_hash TEXT)''')
conn.commit()

registration_form = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Register">
</form>
'''

@app.route('/', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        password_hash = hashlib.sha256(password.encode()).hexdigest()
        
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hash))
        conn.commit()
        
        return f"User {username} registered successfully!"
    else:
        return render_template_string(registration_form)

if __name__ == '__main__':
    app.run(debug=True)