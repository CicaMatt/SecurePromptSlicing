import sqlite3
from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM users WHERE username=?", (username,))
        user = cursor.fetchone()
        conn.close()

        if user and user[1] == password:
            return redirect('/home')
        else:
            return render_template_string('<h1>Invalid username or password</h1>')
    return render_template_string('''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/home')
def home():
    return render_template_string('<h1>Welcome to the Home Page</h1>')

if __name__ == '__main__':
    app.run(debug=True)