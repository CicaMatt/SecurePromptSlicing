from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# HTML templates as strings for simplicity
login_page_html = '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
'''

home_page_html = '''
    <h1>Welcome to the Home Page</h1>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Query the database
        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        
        # Ensure users table exists
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password TEXT NOT NULL
            )
        ''')

        cursor.execute('SELECT * FROM users WHERE username=?', (username,))
        user = cursor.fetchone()

        conn.close()

        if user and user[2] == password:
            return redirect(url_for('home'))
    
    # Render the login page again on failure or GET request
    return render_template_string(login_page_html)

@app.route('/home')
def home():
    return render_template_string(home_page_html)

if __name__ == '__main__':
    app.run(debug=True)


