import sqlite3
from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Connect to SQLite database
conn = sqlite3.connect('users.db', check_same_thread=False)
c = conn.cursor()
c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
conn.commit()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        c.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
        user = c.fetchone()
        
        if user:
            return redirect('/dashboard')
        else:
            return redirect('/login?error=Invalid+credentials')

    error_message = request.args.get('error', '')
    return render_template('login.html', error=error_message)

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)