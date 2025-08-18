from flask import Flask, request, redirect, url_for, render_template_string
from werkzeug.security import generate_password_hash
import sqlite3

app = Flask(__name__)

# Initialize the SQLite database
conn = sqlite3.connect('users.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, 
                                                   username TEXT UNIQUE NOT NULL, 
                                                   password TEXT NOT NULL)''')
conn.commit()

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        hashed_password = generate_password_hash(password)
        
        try:
            cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
            conn.commit()
            return redirect(url_for('register_success'))
        except sqlite3.IntegrityError:
            error_message = "Username already exists. Please choose a different username."
            return render_template_string('''
                <form method="post">
                    Username: <input type="text" name="username"><br>
                    Password: <input type="password" name="password"><br>
                    <input type="submit" value="Register">
                </form>
                <p style="color:red;">{{ error_message }}</p>
            ''', error_message=error_message)
    
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Register">
        </form>
    '''

@app.route('/register_success')
def register_success():
    return 'Registration successful!'

if __name__ == '__main__':
    app.run(debug=True)