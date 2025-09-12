from flask import Flask, request, redirect, render_template, url_for
import sqlite3

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Sample user for testing
    c.execute("INSERT INTO users (username, password) VALUES ('testuser', 'testpass')")
    conn.commit()
    conn.close()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()
        conn.close()
        if user:
            return redirect(url_for('dashboard'))
        else:
            return redirect(url_for('login', error='Invalid credentials'))
    return render_template('login.html', error=request.args.get('error'))

@app.route('/dashboard')
def dashboard():
    return "Welcome to the Dashboard!"

if __name__ == '__main__':
    init_db()
    app.run(debug=True)